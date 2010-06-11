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
	IOError Copy(const StringT1& from, const StringT2& to, bool overwrite)
	{
		if (!overwrite && Core::IO::Exists(to))
			return ioErrOverwriteNotAllowed;

		// Open the source file
		Yuni::Core::IO::File::Stream fromFile(from, OpenMode::read);
		if (fromFile.opened())
		{
			Yuni::Core::IO::File::Stream toFile(to, OpenMode::write | OpenMode::truncate);
			if (toFile.opened())
			{
				char buffer[4096];
				size_t numRead;
				while ((numRead = fromFile.read(buffer, sizeof(buffer))) != 0)
					toFile.write(buffer, numRead);
				return ioErrNone;
			}
		}
		return ioErrNotFound;
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
	Core::IO::IOError
	LoadFromFile(StringT1& out, const StringT2& filename, const uint64 hardlimit)
	{
		out.clear();
		Yuni::Core::IO::File::Stream f(filename);
		if (f.opened())
		{
			char buffer[2096 + 1];
			size_t numRead = 0;
			uint64 totalRead = 0;
			while ((numRead = f.read(buffer, sizeof(buffer) - 1)) != 0)
			{
				// This assignment is mandatory to prevent some bad use with
				// strlen (according to StringT1).
				// In some string implementation, the class might use strlen
				// on the buffer even if the length is given
				buffer[numRead] = '\0';

				totalRead += numRead;
				if (totalRead > hardlimit)
				{
					const size_t minus = totalRead - hardlimit;
					if (minus < numRead)
					{
						numRead -= (totalRead - hardlimit);
						out.append((const char*) buffer, numRead);
					}
					return ioErrMemoryLimit;
				}
				// we use the standard method `append()` to allow the use of std::string
				out.append((const char*) buffer, numRead);
			}
			return ioErrNone;
		}
		return ioErrNotFound;
	}






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_FILES_H__
