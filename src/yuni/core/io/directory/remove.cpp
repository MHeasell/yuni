
#include "../directory.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#ifndef YUNI_OS_MSVC
# include <dirent.h>
# include <unistd.h>
#endif
#ifdef YUNI_OS_WINDOWS
# include "../../system/windows.hdr.h"
# include <ShellApi.h>
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

	bool Remove(const char* path)
	{
		wchar_t* fsource = new wchar_t[FILENAME_MAX];
		int cr;

		(void)::memset(fsource, 0, sizeof(fsource));
		SHFILEOPSTRUCTW shf;
		shf.hwnd = NULL;

		fsource[0] = L'\\';
		fsource[1] = L'\\';
		fsource[2] = L'?';
		fsource[3] = L'\\';
		int n = MultiByteToWideChar(CP_UTF8, 0, path, -1, fsource + 4, FILENAME_MAX - 10);
		if (!n)
		{
			delete fsource;
			return false;
		}
		fsource[n + 4] = L'\0';

		shf.wFunc = FO_DELETE;
		shf.pFrom = fsource;
		shf.pTo = fsource;
		shf.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;

		cr = SHFileOperationW(&shf);
		delete fsource;
		return (!cr);
	}

# else


	namespace // Anonymous namespace
	{

		bool RmDirRecursiveInternal(const char path[])
		{
			DIR* dp;
			struct dirent* ep;
			CustomString<2096> buffer;
			struct stat st;

			if (NULL != (dp = ::opendir(path)))
			{
				while (NULL != (ep = ::readdir(dp)))
				{
					buffer.clear() << path << Yuni::Core::IO::Separator << (const char*)ep->d_name;
					if (0 == ::stat(buffer.c_str(), &st))
					{
						if (S_ISDIR(st.st_mode))
						{
							if (strcmp(".", (ep->d_name)) != 0 && strcmp("..", (ep->d_name)) != 0)
							{
								RmDirRecursiveInternal(buffer.c_str());
								::rmdir(buffer.c_str());
							}
						}
						else
							::unlink(buffer.c_str());
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

