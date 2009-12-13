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


	template<class AnyStringT>
	inline bool Size(const AnyStringT& filename, uint64& size)
	{
		typedef typename Static::Remove::Const<AnyStringT>::Type TypeT;
		return Private::IO::FilesystemImpl::Size(Core::Traits::CString<TypeT>::Buffer(filename), size);
	}


	template<class AnyStringT>
	inline uint64 Size(const AnyStringT& filename)
	{
		typedef typename Static::Remove::Const<AnyStringT>::Type TypeT;
		return Private::IO::FilesystemImpl::Size(Core::Traits::CString<TypeT>::Buffer(filename));
	}




	template<class C>
	inline bool Exists(const C& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsFileWindowsImpl(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(p), Core::Traits::Length<C>::Value(p));
		# else
		return Private::IO::FilesystemImpl::IsFileUnixImpl(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(p));
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


	template<class AnyStringT>
	inline bool CreateEmptyFile(const AnyStringT& filename)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		return file.opened();
	}


	template<class AnyStringT, class U>
	bool SetContent(const AnyStringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class AnyStringT, class U>
	bool AppendContent(const AnyStringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::append);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class AnyStringT1, class AnyStringT2>
	inline bool Copy(const AnyStringT1& from, const AnyStringT2& to, bool overwrite = true)
	{
		return (!overwrite && Core::IO::File::Exists(to))
			? false
			: Private::IO::FilesystemImpl::CopyFile(
				Core::Traits::CString<typename Static::Remove::Const<AnyStringT1>::Type>::Buffer(from),
				Core::Traits::CString<typename Static::Remove::Const<AnyStringT2>::Type>::Buffer(to));
	}


	template<class AnyStringT, class U>
	bool SaveToFile(const AnyStringT& filename, const U& content)
	{
		Core::IO::File::Stream file(filename, OpenMode::write | OpenMode::truncate);
		if (file.opened())
		{
			file += content;
			return true;
		}
		return false;
	}


	template<class C, int ChunkT, class AnyStringT>
	bool LoadContent(const StringBase<C,ChunkT>& out, const AnyStringT& filename, const uint64 hardlimit = sizeHardLimit)
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
				Yuni::Core::IO::File::Stream f(filename, Yuni::Core::IO::File::OpenMode::read);
				if (f.opened())
				{
					out.resize(size);
					if (size == f.read(out.data, size))
						return true;
				}
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
