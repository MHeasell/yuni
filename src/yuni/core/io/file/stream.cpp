
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

	FILE* Stream::OpenFileOnWindows(const char* filename, const OpenMode::Type mode)
	{
		wchar_t buffer[FILENAME_MAX];
		MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, sizeof(buffer));
		return _wfopen(buffer, OpenMode::ToWCString(mode));
	}


# endif


} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

