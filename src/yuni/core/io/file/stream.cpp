
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
		const size_t len = strlen(filename);
		if (!len)
			return NULL;
		wchar_t* buffer = new wchar_t[len + 2];
		const int n = MultiByteToWideChar(CP_UTF8, 0, filename, len, buffer, len);
		if (n <= 0)
		{
			delete[] buffer;
			return NULL;
		}
		buffer[n] = L'\0';
		FILE* f;
		# ifdef YUNI_OS_MSVC
		if (0 != _wfopen_s(&f, buffer, OpenMode::ToWCString(mode)))
			f = NULL;
		# else
		f = _wfopen(buffer, OpenMode::ToWCString(mode));
		# endif
		delete[] buffer;
		return f;
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
			case seekOriginBegin:   return (0 == ::fseek(pFd, (long) offset, SEEK_SET));
			case seekOriginCurrent: return (0 == ::fseek(pFd, (long) offset, SEEK_CUR));
			case seekOriginEnd:     return (0 == ::fseek(pFd, (long) offset, SEEK_END));
		}
		return false;
	}




} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

