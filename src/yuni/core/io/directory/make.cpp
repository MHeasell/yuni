
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

	bool Make(const char path[], unsigned int /* mode */)
	{
		return CreateDirectory(path, NULL);
	}

	# else

	bool Make(const char path[], unsigned int mode)
	{
		if (NULL == path || '\0' == *path)
			return true;

		char buffer[FILENAME_MAX];
		strncpy(buffer, path, sizeof(buffer));
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
					if (::mkdir(buffer, mode) < 0 && errno != EEXIST && errno != EISDIR && errno != ENOSYS)
						return false;
				}
				if ('\0' == tmp)
					break;
				*pt = tmp;
			}
			++pt;
		}
		return true;
	}

	# endif



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

