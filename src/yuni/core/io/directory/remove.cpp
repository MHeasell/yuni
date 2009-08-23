
#include "commons.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{


# ifdef YUNI_OS_WINDOWS

	bool DeleteDirectory(const char* sPath)
	{
		char currentDirectoryPath[MAX_PATH];
		::strcpy(currentDirectoryPath, sPath);
		::strcat(currentDirectoryPath, "\\*");

		char currentFilename[MAX_PATH];
		::strcpy(currentFilename, sPath);
		::strcat(currentFilename, "\\");

		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(currentDirectoryPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE)
			return false;
		::strcpy(currentDirectoryPath, currentFilename);

		bool bSearch = true;
		while (bSearch)
		{
			if (FindNextFile(hFind,&FindFileData))
			{
				if (IsDots(FindFileData.ccurrentFilename))
					continue;
				::strcat(currentFilename, FindFileData.ccurrentFilename);
				if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					if (!DeleteDirectory(currentFilename))
					{
						FindClose(hFind);
						return false;
					}
					RemoveDirectory(currentFilename);
					::strcpy(currentFilename, currentDirectoryPath);
				}
				else
				{
					if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
						_chmod(currentFilename, _S_IWRITE);
					if (!DeleteFile(currentFilename))
					{
						FindClose(hFind);
						return false;
					}
					strcpy(currentFilename, currentDirectoryPath);
				}
			}
			else
			{
				if (GetLastError() == ERROR_NO_MORE_FILES)
					bSearch = false;
				else
				{
					FindClose(hFind);
					return false;
				}
			}
		}

		FindClose(hFind);
		return RemoveDirectory(sPath);
	}

	bool Remove(const char* path)
	{
		return (NULL == path || '\0' == *path) ? true : RmDirUnixImpl(path);
	}


# else

	namespace
	{

		bool RmDirUnixImpl(const char path[])
		{
			DIR* dp;
			if (NULL != (dp = ::opendir(path)))
			{
				struct dirent* ep;
				struct stat st;
				// temp Buffer
				char buffer[FILENAME_MAX];

				while (NULL != (ep = ::readdir(dp)))
				{
					sprintf(buffer, "%s/%s", path, ep->d_name);
					if (0 == ::stat(buffer, &st))
					{
						if (S_ISDIR(st.st_mode))
						{
							if (strcmp(".", (ep->d_name)) != 0 && strcmp("..", (ep->d_name)) != 0)
							{
								if (!RmDirUnixImpl(buffer))
									return false;
								if (::rmdir(buffer))
									return false;
							}
						}
						else
							::unlink(buffer);
					}
				}
				(void)::closedir(dp);
			}
			return (0 == ::rmdir(path));
		}

	} // anonymous namespace



	bool Remove(const char* path)
	{
		return (NULL == path || '\0' == *path) ? true : RmDirUnixImpl(path);
	}


# endif

} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

