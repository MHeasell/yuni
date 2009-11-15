
#include "../directory.h"
#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#ifdef YUNI_OS_WINDOWS
# include "../../system/windows.hdr.h"
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

	bool Remove(const char* path)
	{
		wchar_t fsource[MAX_PATH];
		int cr;

		(void)::memset(fsource, 0, sizeof(fsource));
		SHFILEOPSTRUCTW shf;
		shf.hwnd = NULL;

		MultiByteToWideChar(CP_UTF8, 0, path, -1, fsource, sizeof(fsource) - 1);

		shf.wFunc = FO_DELETE;
		shf.pFrom = fsource;
		shf.pTo = fsource;
		shf.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;

		cr = SHFileOperationW(&shf);
		return (!cr);
	}

# else


	namespace // Anonymous namespace
	{

		bool RmDirRecursiveInternal(const char path[])
		{
			DIR* dp;
			struct dirent* ep;
			char buffer[FILENAME_MAX];
			struct stat st;

			if (NULL != (dp = ::opendir(path)))
			{
				while (NULL != (ep = ::readdir(dp)))
				{
					(void)::sprintf(buffer, "%s/%s", path, ep->d_name);
					if (0 == ::stat(buffer, &st))
					{
						if (S_ISDIR(st.st_mode))
						{
							if (strcmp(".", (ep->d_name)) != 0 && strcmp("..", (ep->d_name)) != 0)
							{
								RmDirRecursiveInternal(buffer);
								::rmdir(buffer);
							}
						}
						else
							::unlink(buffer);
					}
				}
				(void)::closedir(dp);
			}
			return (0 == rmdir(path));
		}

	} // anonymous namespace




	bool Remove(const char path[])
	{
		if (NULL == path || '\0' == *path)
			return true;
		return RmDirRecursiveInternal(path);
	}


# endif



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni

