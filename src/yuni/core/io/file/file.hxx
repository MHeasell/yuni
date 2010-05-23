#ifndef __YUNI_CORE_FS_FILES_HXX__
# define __YUNI_CORE_FS_FILES_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"



namespace Yuni
{
namespace Private
{
namespace Core
{
namespace IO
{

	bool Size(const char* filename, unsigned int len, uint64& value);
	bool SizeNotZeroTerminated(const char* filename, unsigned int len, uint64& value);

} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni



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
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CoreIOFileSize_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CoreIOFileSize_InvalidTypeForLength);

		if (Traits::CString<StringT>::zeroTerminated)
		{
			return Yuni::Private::Core::IO::Size(
				Traits::CString<StringT>::Perform(filename), Traits::Length<StringT,size_t>::Value(filename), size);
		}
		else
		{
			return Yuni::Private::Core::IO::Size(
				Traits::CString<StringT>::Perform(filename), Traits::Length<StringT,size_t>::Value(filename), size);
		}
	}


	template<class StringT>
	inline uint64 Size(const StringT& filename)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CoreIOFileSize_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CoreIOFileSize_InvalidTypeForLength);

		uint64 size;

		if (Traits::CString<StringT>::zeroTerminated)
		{
			return Yuni::Private::Core::IO::Size(
				Traits::CString<StringT>::Perform(filename), Traits::Length<StringT,size_t>::Value(filename), size)
				? size : 0;
		}
		else
		{
			return Yuni::Private::Core::IO::Size(
				Traits::CString<StringT>::Perform(filename), Traits::Length<StringT,size_t>::Value(filename), size)
				? size : 0;
		}
	}




	template<class StringT> inline bool Exists(const StringT& filename)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, IOFileExists_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  IOFileExists_InvalidTypeForBufferSize);

		return ((Yuni::Core::IO::typeFile & Yuni::Core::IO::TypeOf(filename)) != 0);
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
	bool Copy(const StringT1& from, const StringT2& to, bool overwrite)
	{
		if (!overwrite && Core::IO::File::Exists(to))
			return false;

		// Open the source file
		Yuni::Core::IO::File::Stream fromFile(from, Yuni::Core::IO::File::OpenMode::read);
		if (fromFile.opened())
		{
			Yuni::Core::IO::File::Stream toFile(to,
				Yuni::Core::IO::File::OpenMode::write | Yuni::Core::IO::File::OpenMode::truncate);
			if (toFile.opened())
			{
				char buffer[4096];
				size_t numRead;
				while ((numRead = fromFile.read(buffer, sizeof(buffer))))
					toFile.write(buffer, numRead);
				return true;
			}
		}
		return false;
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



	template<class StringT1, class StringT2>
	bool LoadContent(StringT1& out, const StringT2& filename, const uint64 hardlimit)
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
