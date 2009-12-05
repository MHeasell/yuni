
#include "stream.h"
#include "../../system/windows.hdr.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{

	Stream::Stream(const Stream&)
		:pFd(NULL)
	{
		// Do nothing
	}


# ifdef YUNI_OS_WINDOWS

	FILE* Stream::OpenFileOnWindows(const char* filename, const int mode)
	{
		wchar_t buffer[FILENAME_MAX];
		MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, sizeof(buffer));
		return _wfopen(buffer, OpenMode::ToWCString(mode));
	}


# endif

	bool Stream::close()
	{
		if (pFd)
		{
			if (0 == ::fclose(pFd))
			{
				pFd = NULL;
				return true;
			}
			return false;
		}
		return true;
	}


	bool Stream::seek(ssize_t offset, SeekOrigin origin)
	{
		switch (origin)
		{
			case seekOriginBegin:   return (0 == ::fseek(pFd, offset, SEEK_SET));
			case seekOriginCurrent: return (0 == ::fseek(pFd, offset, SEEK_CUR));
			case seekOriginEnd:     return (0 == ::fseek(pFd, offset, SEEK_END));
		}
		return false;
	}



} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

