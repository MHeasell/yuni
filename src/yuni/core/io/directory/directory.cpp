
#include "commons.h"



namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{


	bool Copy(const char* src, const char* dst)
	{
		struct stat sb;
		if (::stat(src, &sb))
			return 0;

		DIR *dirp;
		struct dirent *dp;
		int fd, fd2;
		mode_t mode;
		char buf[FILENAME_MAX];

		/* src is a file */
		if (!S_ISDIR((mode = sb.st_mode)))
		{
			if (!::stat(dst, &sb) && S_ISDIR(sb.st_mode))
			{
				const char *p = strrchr(src, '/');
				/* src => dst/src */
				::sprintf(buf, "%s/%s", dst, (p?p+1:src));

				IO::Directory::Copy(src, buf);
				return 1;
			}

			//LogNotice("Copying `%s`", ShortPath(src, buf, 60));
			/* src => dst */
			if ((fd = ::open(src, O_RDONLY)) < 0)
				return 0;

			if ((fd2 = ::open(dst, O_CREAT|O_TRUNC|O_WRONLY, mode & 0777)) < 0)
			{
				close(fd);
				return 0;
			}

			size_t len, len2;
			while ((len = ::read(fd, buf, FILENAME_MAX)) > 0)
			{
				while (len && (len2 = write(fd2, buf, len)) > 0)
					len -= len2;
			}
			::close(fd);
			::close(fd2);

			return 1;
		}

		/* src is a directory */
		if (::stat(dst, &sb))
		{
			if (!IO::Directory::Make(dst))
				return 0;
		}
		else
		{
			/* if dst already exists and it's a file, try to remove it */
			if (!S_ISDIR(sb.st_mode))
			{
				if (::remove(dst) || !IO::Directory::Make(dst))
					return false;
			}
		}

		if ((dirp = ::opendir(src)) == NULL)
			return false;

		char buf2[FILENAME_MAX];
		while ((dp = ::readdir(dirp)) != NULL)
		{
			/* do not copy hidden files */
			if (dp->d_name[0] == '.')
				continue;
			::sprintf(buf, "%s/%s", src, dp->d_name);
			::sprintf(buf2, "%s/%s", dst, dp->d_name);
			IO::Directory::Copy(buf, buf2);
		}
		::closedir(dirp);

		return true;
	}




} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

