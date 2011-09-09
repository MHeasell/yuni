
#include "../io.h"
#include "../directory.h"
#include <errno.h>
#ifdef YUNI_HAS_STDLIB_H
# include <stdlib.h>
#endif
#ifndef YUNI_OS_MSVC
# include <dirent.h>
# include <unistd.h>
#endif
#ifdef YUNI_OS_WINDOWS
# include "../../core/system/windows.hdr.h"
# include <shellapi.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include "../../core/string.h"
#include "../../core/customstring/wstring.h"
#include <stdio.h>


#define SEP Yuni::IO::Separator



namespace Yuni
{
namespace IO
{
namespace Directory
{


# ifndef YUNI_OS_WINDOWS


	namespace // Anonymous namespace
	{

		static bool RmDirRecursiveInternal(const char* path)
		{
			DIR* dp;
			struct dirent* ep;
			CString<2096> buffer;
			struct stat st;

			if (NULL != (dp = ::opendir(path)))
			{
				while (NULL != (ep = ::readdir(dp)))
				{
					buffer.clear() << path << SEP << (const char*)ep->d_name;
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


	# endif




	bool Remove(const StringAdapter& path)
	{
		if (path.empty())
			return true;

		# ifdef YUNI_OS_WINDOWS
		Private::WString<true> fsource(path);
		if (fsource.empty())
			return false;

		SHFILEOPSTRUCTW shf;
		shf.hwnd = NULL;

		shf.wFunc = FO_DELETE;
		shf.pFrom = fsource.c_str();
		shf.pTo = fsource.c_str();
		shf.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;

		const int cr = SHFileOperationW(&shf);
		return (!cr);

		# else
		return RmDirRecursiveInternal(path.c_str());
		# endif
	}






} // namespace Directory
} // namespace IO
} // namespace Yuni

