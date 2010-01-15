
#include "io.h"
#include "../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
#	include <stdlib.h>
#	include <unistd.h>
#	include <sys/types.h>
#endif
#include <sys/stat.h>


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

	bool ExistsWindowsImpl(const char* p, const size_t len)
	{
		if (len)
		{
			// ugly workaround with stat under Windows
			// FIXME: Find a better way to find driver letters
			if (':' == *(p + 1))
			{
				if ('\0' == *(p + 2) || ('\\' == *(p + 2) && '\0' == *(p + 3)))
					return true;
			}

			struct _stati64 s;
			wchar_t buffer[FILENAME_MAX];
			// On Windows, the trailing backslash must be removed
			MultiByteToWideChar(CP_UTF8, 0, p, len - (('\\' == p[len - 1]) ? 1 : 0), buffer, sizeof(buffer));
			return (_wstati64(buffer, &s) == 0);
		}
		return false;
	}

	template<bool B>
	bool IsDirWindowsImpl(const char* p, const size_t len)
	{
		// ugly workaround with stat under Windows
		// FIXME: Find a better way to find driver letters
		if (':' == *(p + 1))
		{
			if ('\0' == *(p + 2) || ('\\' == *(p + 2) && '\0' == *(p + 3)))
				return true;
		}

		struct _stati64 s;
		wchar_t buffer[FILENAME_MAX];
		// On Windows, the trailing backslash must be removed
		MultiByteToWideChar(CP_UTF8, 0, p, len - (('\\' == p[len - 1]) ? 1 : 0), buffer, sizeof(buffer));
		if (_wstati64(buffer, &s) != 0)
			return false;
		return (B == S_ISDIR(s.st_mode));
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

