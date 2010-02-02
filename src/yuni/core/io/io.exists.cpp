
#include "io.h"
#include "../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
#	include <stdlib.h>
#	include <unistd.h>
#	include <sys/types.h>
#endif
#include <sys/stat.h>
#include "../utils/hexdump.h"


#ifndef S_ISDIR
#	define S_ISDIR(mode) ( (mode & S_IFMT) == S_IFDIR)
#endif

#include "../utils/hexdump.cpp"


namespace Yuni
{
namespace Private
{
namespace IO
{
namespace FilesystemImpl
{

	# ifdef YUNI_OS_WINDOWS

	bool ExistsWindowsImpl(const char* p, const size_t len)
	{
		if (!len)
			return false;
		// ugly workaround with stat under Windows
		// FIXME: Find a better way to find drive letters
		if (':' == *(p + 1))
		{
			if ('\0' == *(p + 2) || ('\\' == *(p + 2) && '\0' == *(p + 3)))
				return true;
		}

		// Conversion into wchar_t
		wchar_t buffer[FILENAME_MAX];
		int n = MultiByteToWideChar(CP_UTF8, 0, p, len - (('\\' == p[len - 1]) ? 1 : 0), buffer, sizeof(buffer));
		for (int i = 0; i < n; ++i)
		{
			if (buffer[i] == '/')
				buffer[i] = '\\';
		}
		buffer[n] = L'\0';

 		WIN32_FILE_ATTRIBUTE_DATA infoFile; 
		return (GetFileAttributesExW(buffer, GetFileExInfoStandard, &infoFile));
	}

	template<bool B>
	bool IsDirWindowsImpl(const char* p, const size_t len)
	{
		if (!len)
			return false;
		// ugly workaround with stat under Windows
		// FIXME: Find a better way to find drive letters
		if (':' == *(p + 1))
		{
			if ('\0' == *(p + 2) || ('\\' == *(p + 2) && '\0' == *(p + 3)))
				return true;
		}

		// Conversion into wchar_t
		wchar_t buffer[FILENAME_MAX];
		int n = MultiByteToWideChar(CP_UTF8, 0, p, len - (('\\' == p[len - 1]) ? 1 : 0), buffer, sizeof(buffer));
		for (int i = 0; i < n; ++i)
		{
			if (buffer[i] == '/')
				buffer[i] = '\\';
		}
		buffer[n] = L'\0';

 		WIN32_FILE_ATTRIBUTE_DATA infoFile; 
		if (!GetFileAttributesExW(buffer, GetFileExInfoStandard, &infoFile))
			return false;
		return (B == (infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
	}


	bool IsDirectoryWindowsImpl(const char* p, const size_t sizeHint)
	{
		return IsDirWindowsImpl<true>(p, sizeHint);
	}

	bool IsFileWindowsImpl(const char* p, const size_t sizeHint)
	{
		return IsDirWindowsImpl<false>(p, sizeHint);
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

