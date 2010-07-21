
#include "../directory.h"
#include <string.h>
#include <errno.h>
#ifdef YUNI_HAS_STDLIB_H
# include <stdlib.h>
#endif
#ifndef YUNI_OS_MSVC
# include <dirent.h>
# include <unistd.h>
#endif
#ifdef YUNI_OS_WINDOWS
# include "../../system/windows.hdr.h"
# include <shellapi.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>




namespace Yuni
{
namespace Private
{
namespace Core
{
namespace IO
{
namespace Directory
{


	# ifdef YUNI_OS_WINDOWS

	bool Copy(const char* src, unsigned int srclen, const char* dst, unsigned int dstlen)
	{
		// ref: http://msdn.microsoft.com/en-us/library/bb759795(v=VS.85).aspx

		wchar_t* fsource = new wchar_t[srclen + 4];
		wchar_t* fcible  = new wchar_t[dstlen + 4];

		SHFILEOPSTRUCTW shf;
		shf.hwnd = NULL;

		int n = MultiByteToWideChar(CP_UTF8, 0, src, srclen, fsource, srclen);
		if (n <= 0)
			return false;
		fsource[n]     = L'\0'; // This string must be double-null terminated
		fsource[n + 1] = L'\0';

		n = MultiByteToWideChar(CP_UTF8, 0, dst, dstlen, fcible, dstlen);
		if (n <= 0)
			return false;
		fcible[n]     = L'\0'; // This string must be double-null terminated
		fcible[n + 1] = L'\0';

		shf.wFunc  = FO_COPY;
		shf.pFrom  = fsource;
		shf.pTo    = fcible;
		shf.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;

		int r = SHFileOperationW(&shf);
		return (!r);
	}


# else

	bool FileCopy(const char* src, const char* dst, unsigned int mode)
	{
		int fd, fd2;
		if ((fd = ::open(src, O_RDONLY)) < 0)
			return false;

		if ((fd2 = ::open(dst, O_CREAT|O_TRUNC|O_WRONLY, mode & 0777)) < 0)
		{
			(void)::close(fd);
			return false;
		}

		char buf[FILENAME_MAX];
		ssize_t len, len2;
		while ((len = ::read(fd, buf, sizeof(buf))) > 0)
		{
			while (len && (len2 = write(fd2, buf, (size_t)len)) > 0)
				len -= len2;
		}

		(void)::close(fd);
		(void)::close(fd2);

		return true;
	}


	bool Copy(const char* src, unsigned int srclen, const char* dst, unsigned int dstlen)
	{
		CustomString<1024> buf;
		CustomString<1024> buf2;

		buf.assign(src, srclen);
		struct stat sb;
		if (::stat(buf.c_str(), &sb))
			return false;

		mode_t mode;

		// src is a file
		if (!S_ISDIR((mode = sb.st_mode)))
		{
			if (!::stat(dst, &sb) && S_ISDIR(sb.st_mode))
			{
				const char *p = strrchr(src, '/');
				// src => dst/src
				buf.assign(dst, dstlen);
				buf << '/' << (p ? p + 1 : src);
				return Copy(src, srclen, buf.c_str(), buf.size());
			}

			// Copy the file
			buf.assign(src, srclen);
			buf2.assign(dst, dstlen);
			return FileCopy(buf.c_str(), buf2.c_str(), mode);
		}

		// src is a directory
		buf2.assign(dst, dstlen);
		if (::stat(buf2.c_str(), &sb))
		{
			// 'dst' does not exist yet
			// We have to create it
			if (!Private::Core::IO::Directory::UnixMake(dst, dstlen))
				return false;
		}
		else
		{
			// 'dst' already exists
			// We have to remove it first (if not a directory) then to recreate it
			if (!S_ISDIR(sb.st_mode))
			{
				if (::remove(buf2.c_str()) || !Private::Core::IO::Directory::UnixMake(dst, dstlen))
					return false;
			}
		}

		buf.assign(src, srclen);
		DIR *dirp;
		struct dirent *dp;
		if ((dirp = ::opendir(buf.c_str())) == NULL)
			return false;
		while ((dp = ::readdir(dirp)) != NULL)
		{
			// Do not copy '.' or '..' but can copy hidden directories
			if ('.' == dp->d_name[0] && ('.' == dp->d_name[1] || '\0' == dp->d_name[1]))
				continue;

			buf.assign(src, srclen);
			buf << '/' << (const char*) dp->d_name;
			buf2.assign(dst, dstlen);
			buf2 << '/' << (const char*) dp->d_name;
			if (!Copy(buf.c_str(), buf.size(), buf2.c_str(), buf2.size()))
			{
				::closedir(dirp);
				return false;
			}
		}
		::closedir(dirp);
		return true;
	}

# endif




} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni

