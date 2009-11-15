
#include "../directory.h"
#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#ifdef YUNI_OS_WINDOWS
# include "../../core/system/windows.hdr.h"
# include <ShellApi.h>
#endif
#include <sys/stat.h>
#include <unistd.h>
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

	bool Copy(const char* src, const char* dst)
	{
		wchar_t fsource[MAX_PATH];
		wchar_t fcible[MAX_PATH];
		int cr;

		SHFILEOPSTRUCTW shf;
		shf.hwnd = NULL;

		MultiByteToWideChar(CP_UTF8, 0, src, -1, fsource, sizeof(fsource) - 1);
		MultiByteToWideChar(CP_UTF8, 0, dst, -1, fcible, sizeof(fcible) - 1);

		shf.wFunc = FO_COPY;
		shf.pFrom = fsource;
		shf.pTo = fcible;
		shf.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;

		cr = SHFileOperationW(&shf);
		return (!cr);
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


	bool Copy(const char* src, const char* dst)
	{
		struct stat sb;

		if (::stat(src, &sb))
			return false;

		char buf[FILENAME_MAX];
		char buf2[FILENAME_MAX];
		mode_t mode;

		// src is a file
		if (!S_ISDIR((mode = sb.st_mode)))
		{
			if (!::stat(dst, &sb) && S_ISDIR(sb.st_mode))
			{
				const char *p = strrchr(src, '/');
				// src => dst/src
				strncpy(buf, dst, sizeof(buf) - 1);
				strncat(buf, (p ? p + 1 : src), sizeof(buf) - 1);
				return Copy(src, buf);
			}

			// Copy the file
			return FileCopy(src, dst, mode);
		}

		/* src is a directory */

		if (::stat(dst, &sb))
		{
			// 'dst' does not exist yet
			// We have to create it
			if (!Private::Core::IO::Directory::UnixMake(dst))
				return false;
		}
		else
		{
			// 'dst' already exists
			// We have to remove it first (if not a directory) then to recreate it
			if (!S_ISDIR(sb.st_mode))
			{
				if (::remove(dst) || !Private::Core::IO::Directory::UnixMake(dst))
					return false;
			}
		}

		DIR *dirp;
		struct dirent *dp;
		if ((dirp = ::opendir(src)) == NULL)
			return false;
		while ((dp = ::readdir(dirp)) != NULL)
		{
			// Do not copy '.' or '..' but can copy hidden directories
			if ('.' == dp->d_name[0] && ('.' == dp->d_name[1] || '\0' == dp->d_name[1]))
				continue;

			sprintf(buf, "%s/%s", src, dp->d_name);
			sprintf(buf2, "%s/%s", dst, dp->d_name);
			if (!Copy(buf, buf2))
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


