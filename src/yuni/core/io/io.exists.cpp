
#include "io.h"
#include "../system/windows.hdr.h"
#include <sys/stat.h>
#ifndef YUNI_OS_WINDOWS
#	include <stdlib.h>
#	include <unistd.h>
#endif


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
		// ugly workaround with stat under Windows
		// FIXME: Find a better way to find driver letters
		if (':' == *(p + 1))
		{
			if ('\0' == *(p + 2) || ('\\' == *(p + 2) && '\0' == *(p + 3)))
				return true;
		}

		struct _stat s;
		size_t l = ::strlen(p);
		// On Windows, the trailing backslash must be removed
		if ('\\' == p.last())
		{
			return (_stat(String(p, p.size() - 1).c_str(), &s) == 0);
		}
		return (_stat(p, &s) == 0);
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

		struct _stat s;
		size_t l = ::strlen(p);
		// On Windows, the trailing backslash must be removed
		if ('\\' == p.last())
		{
			if (_stat(String(p, p.size() - 1).c_str(), &s) != 0)
				return false;
		}
		if (_stat(p, &s) != 0)
			return false;
		return (B == S_ISDIR(s.st_mode));
	}

	bool IsDirectoryWindowsImpl(const char* p)
	{
		return IsDirWindowImpl<true>(p);
	}

	bool IsFileWindowsImpl(const char* p)
	{
		return IsDirWindowsImpl<false>(p);
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
		struct stat s;
		if (stat(p, &s) != 0)
			return false;
		return (B == S_ISDIR(s.st_mode));
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

