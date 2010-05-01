#include "io.h"
#include "../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
#else
#include <sys/stat.h>
#endif
#include "../customstring.h"


#ifndef S_ISDIR
#	define S_ISDIR(mode) ( (mode & S_IFMT) == S_IFDIR)
#endif




namespace Yuni
{
namespace Private
{
namespace IO
{
namespace FilesystemImpl
{

	# ifdef YUNI_OS_WINDOWS

	template<bool ExistsOnlyT, bool ResultT>
	bool IsDirWindowsImpl(const char* p, size_t len)
	{
		if (!len)
			return false;
		if (p[len - 1] == '\\' || p[len - 1] == '/')
		{
			if (!--len)
			{
				# ifdef YUNI_OS_WINDOWS
				return false;
				# else
				// On Unixes, `/` is a valid folder
				return true;
				# endif
			}
		}
		# ifdef YUNI_OS_WINDOWS
		// Driver letters
		if (len == 2 && p[1] == ':')
			return true;
		# endif

		CustomString<>  norm;
		Yuni::Core::IO::Normalize(norm, p, len);
		// Conversion into wchar_t
		wchar_t* buffer = new wchar_t[norm.size() + 10];
		buffer[0] = L'\\';
		buffer[1] = L'\\';
		buffer[2] = L'?';
		buffer[3] = L'\\';
		int n = MultiByteToWideChar(CP_UTF8, 0, norm.c_str(), norm.size(), buffer + 4, norm.size());
		if (!n)
		{
			delete buffer;
			return false;
		}
		for (int i = 4; i < n + 4; ++i)
		{
			if (buffer[i] == '/')
				buffer[i] = '\\';
		}
		buffer[n + 4] = L'\0';

		WIN32_FILE_ATTRIBUTE_DATA infoFile;
		if (!GetFileAttributesExW(buffer, GetFileExInfoStandard, &infoFile))
		{
			delete[] buffer;
			return false;
		}
		delete[] buffer;

		# ifdef YUNI_OS_MSVC
		return (ExistsOnlyT)
			? true
			: ((ResultT == (bool)(infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) ? true : false;
		# else
		return (ExistsOnlyT)
			? true
			: (ResultT == (bool)(infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
		# endif
	}


	bool ExistsWindowsImpl(const char* p, const size_t len)
	{
		return IsDirWindowsImpl<true, false>(p, len);
	}


	bool IsDirectoryWindowsImpl(const char* p, const size_t sizeHint)
	{
		return IsDirWindowsImpl<false, true>(p, sizeHint);
	}

	bool IsFileWindowsImpl(const char* p, const size_t sizeHint)
	{
		return IsDirWindowsImpl<false, false>(p, sizeHint);
	}


	# else

	bool ExistsUnixImpl(const char* p)
	{
		struct stat s;
		return (stat(p, &s) == 0);
	}

	template<bool B>
	inline bool IsDirUnixImpl(const char* p)
	{
		if (p && '\0' != *p)
		{
			struct stat s;
			if (stat(p, &s) != 0)
				return false;
			return (B == S_ISDIR(s.st_mode));
		}
		return false;
	}


	bool IsDirectoryUnixImpl(const char* p)
	{
		return IsDirUnixImpl<true>(p);
	}

	bool IsFileUnixImpl(const char* p)
	{
		return IsDirUnixImpl<false>(p);
	}

	# endif



} // namespace FilesystemImpl
} // namespace IO
} // namespace Private
} // namespace Yuni
