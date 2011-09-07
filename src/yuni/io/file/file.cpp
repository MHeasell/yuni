
#include <sys/stat.h>
#include "../file.h"
#include "../directory.h"
#include <ctype.h>
#include <string.h>
#include "../../core/customstring/wstring.h"

#ifndef YUNI_OS_WINDOWS
# include <unistd.h>
#endif
#if defined(YUNI_OS_LINUX) && defined(YUNI_HAS_SYS_SENDFILE_H)
# include <sys/sendfile.h>
#endif



namespace Yuni
{
namespace Private
{
namespace IO
{


	# ifdef YUNI_OS_WINDOWS

	bool Size(const char* const filename, unsigned int len, uint64& value)
	{
		if (!len)
		{
			value = 0u;
			return false;
		}

		const char* const p = filename;

		if (p[len - 1] == '\\' || p[len - 1] == '/')
			--len;

		// Driver letters
		if (len == 2 && p[1] == ':')
		{
			value = 0u;
			return true;
		}

		String  norm;
		Yuni::IO::Normalize(norm, p, len);
		// Conversion into wchar_t
		WString<true> wstr(norm);
		if (wstr.empty())
		{
			value = 0u;
			return false;
		}

		HANDLE hndl = CreateFileW(wstr.c_str(), 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hndl == INVALID_HANDLE_VALUE)
		{
			value = 0u;
			return false;
		}
		LARGE_INTEGER v;
		if (!GetFileSizeEx(hndl, &v))
		{
			CloseHandle(hndl);
			value = 0u;
			return false;
		}
		value = (uint64) v.QuadPart;

		CloseHandle(hndl);
		return true;
	}

	# else

	bool Size(const char* const filename, unsigned int, uint64& value)
	{
		struct stat results;
		if (filename && '\0' != *filename && stat(filename, &results) == 0)
		{
			value = static_cast<uint64>(results.st_size);
			return true;
		}
		value = 0u;
		return false;
	}

	# endif



	bool SizeNotZeroTerminated(const char* filename, unsigned int len, uint64& value)
	{
		# ifdef YUNI_OS_WINDOWS
		// on Windows, we already have to use temporary buffers
		return Yuni::Private::IO::Size(filename, len, value);
		# else
		if (len < 1020)
		{
			CString<1024, false, true> copy;
			copy.assign(filename, len);
			return Yuni::Private::IO::Size(copy.c_str(), copy.size(), value);
		}
		else
		{
			char* p = new char[len + 1];
			(void)::memcpy(p, filename, len * sizeof(char));
			p[len] = '\0';
			bool r = Yuni::Private::IO::Size(p, len, value);
			delete[] p;
			return r;
		}
		# endif
	}



	Yuni::IO::Error YnDeleteFile(const char* const filename, unsigned int len)
	{
		if (!len)
			return Yuni::IO::errUnknown;

		# ifndef YUNI_OS_WINDOWS
		if (unlink(filename))
			return Yuni::IO::errUnknown;
		return Yuni::IO::errNone;
		# else

		const char* const p = filename;

		if (p[len - 1] == '\\' || p[len - 1] == '/')
			--len;

		// Driver letters
		if (len == 2 && p[1] == ':')
			return Yuni::IO::errBadFilename;

		String  norm;
		Yuni::IO::Normalize(norm, p, len);
		// Conversion into wchar_t
		WString<true> wstr(norm);
		if (wstr.empty())
			return Yuni::IO::errUnknown;
		wstr.replace('/', '\\');

		if (DeleteFileW(wstr.c_str()))
			return Yuni::IO::errNone;
		return Yuni::IO::errUnknown;
		# endif
	}


	Yuni::IO::Error DeleteFileNotZeroTerminated(const char* const filename, unsigned int len)
	{
		# ifndef YUNI_OS_WINDOWS
		if (len < 1020)
		{
			CString<1024, false, true> copy;
			copy.assign(filename, len);
			return YnDeleteFile(copy.c_str(), copy.size());
		}
		else
		{
			CString<> copy;
			copy.assign(filename, len);
			return YnDeleteFile(copy.c_str(), copy.size());
		}
		# else
		return YnDeleteFile(filename, len);
		# endif
	}


	Yuni::IO::Error Copy(Yuni::IO::File::Stream& in, Yuni::IO::File::Stream& out)
	{
		enum { size = 8192 };

		# if defined(YUNI_OS_LINUX) && defined(YUNI_HAS_SYS_SENDFILE_H)
		{
			const int fdIN  = fileno(in. nativeHandle());
			const int fdOUT = fileno(out.nativeHandle());

			// Trying sendfile first
			struct stat st;
			if (!fstat(fdIN, &st))
			{
				off_t offset = 0;
				if (-1 != sendfile(fdOUT, fdIN, &offset, (size_t) st.st_size))
					return Yuni::IO::errNone;
			}

			// fallback to the standard copy
			char* buffer = new char[size];
			size_t numRead;

			while((numRead = read(fdIN, buffer, size)) > 0)
				write(fdOUT, buffer, numRead);

			delete[] buffer;
			return Yuni::IO::errNone;
		}

		# else

		// Generic implementation
		char* buffer = new char[size];
		size_t numRead;
		while ((numRead = in.read(buffer, size)) != 0)
			out.write(buffer, numRead);
		delete[] buffer;
		return Yuni::IO::errNone;

		# endif
	}




} // namespace IO
} // namespace Private
} // namespace Yuni

