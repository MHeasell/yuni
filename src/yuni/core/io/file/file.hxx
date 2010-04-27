#ifndef __YUNI_CORE_FS_FILES_HXX__
# define __YUNI_CORE_FS_FILES_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{


	template<class StringT>
	inline bool Size(const StringT& filename, uint64& size)
	{
		typedef typename Static::Remove::Const<StringT>::Type TypeT;
		return Private::IO::FilesystemImpl::Size(Traits::CString<TypeT>::Perform(filename), size);
	}


	template<class StringT>
	inline uint64 Size(const StringT& filename)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<StringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, CoreIOFileSize_InvalidTypeForBuffer);

		return Private::IO::FilesystemImpl::Size(Traits::CString<UType>::Perform(filename));
	}




	template<class StringT> inline bool Exists(const StringT& filename)
	{
		// The given type, without its const identifier
		typedef typename Static::Remove::Const<StringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, IOFileExists_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  IOFileExists_InvalidTypeForBufferSize);

		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsFileWindowsImpl(
			Traits::CString<UType>::Perform(filename), Traits::Length<UType,size_t>::Value(filename));
		# else
		return Private::IO::FilesystemImpl::IsFileUnixImpl(Traits::CString<UType>::Perform(filename));
		# endif
	}


	template<int N>
	inline bool Load(String::Vector& out, const StringBase<char,N>& filename, const bool emptyListBefore,
		const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}

	template<int N>
	inline bool Load(String::List& out, const StringBase<char,N>& filename, const bool emptyListBefore,
		const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}


	template<class StringT>
	inline bool CreateEmptyFile(const StringT& filename)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		return file.opened();
	}


	template<class StringT, class U>
	bool SetContent(const StringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class StringT, class U>
	bool AppendContent(const StringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::append);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class StringT1, class StringT2>
	bool Copy(const StringT1& from, const StringT2& to, bool overwrite = true)
	{
		return (!overwrite && Core::IO::File::Exists(to))
			? false
			: Private::IO::FilesystemImpl::CopyFile(
				Traits::CString<StringT1>::Perform(from),
				Traits::CString<StringT2>::Perform(to));
	}


	template<class StringT, class U>
	bool SaveToFile(const StringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}



	template<class C, int ChunkT, class StringT>
	bool LoadContent(StringBase<C,ChunkT>& out, const StringT& filename, const uint64 hardlimit = sizeHardLimit)
	{
		uint64 size;
		if (Core::IO::File::Size(filename, size))
		{
			if (size)
			{
				if (size > hardlimit)
				{
					out.clear();
					return false;
				}
				Yuni::Core::IO::File::Stream f(filename);
				if (f.opened())
				{
					out.resize(size);
					if (size == f.read(out))
						return true;
				}
				return false;
			}
			out.clear();
			return true;
		}
		out.clear();
		return false;
	}






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_FILES_H__
