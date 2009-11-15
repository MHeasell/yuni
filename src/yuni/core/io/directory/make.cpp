
#include "../directory.h"
#include "commons.h"


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

	bool WindowsMake(const char* path)
	{
		if (!Yuni::Core::IO::Exists(path))
		{
			wchar_t buffer[FILENAME_MAX];
			MultiByteToWideChar(CP_UTF8, 0, path, -1, buffer, sizeof(buffer));

			wchar_t* t = buffer;
			while (0 != t)
			{
				if (*t == L'\\' || *t == L'/')
				{
					*t = L'\0';
					if (!CreateDirectoryW(buffer, NULL))
						return false;
					*t = L'\\';
				}
				++t;
			}
			if (!CreateDirectoryW(buffer, NULL))
				return false;
		}
		return true;
	}

	# else

	bool UnixMake(const char* path, unsigned int mode)
	{
		if (NULL == path || '\0' == *path)
			return true;

		if (!Yuni::Core::IO::Exists(path))
		{
			char buffer[FILENAME_MAX];
			(void)::strncpy(buffer, path, sizeof(buffer));
			char* pt = buffer;
			char tmp;

			while (1)
			{
				if ('\\' == *pt || '/' == *pt || '\0' == *pt)
				{
					tmp = *pt;
					*pt = '\0';
					if ('\0' != buffer[0] && '\0' != buffer[1] && '\0' != buffer[2])
					{
						if (mkdir(buffer, mode) < 0 && errno != EEXIST && errno != EISDIR && errno != ENOSYS)
							return false;
					}
					if ('\0' == tmp)
						break;
					*pt = tmp;
				}
				++pt;
			}
		}
		return true;
	}

# endif



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni

