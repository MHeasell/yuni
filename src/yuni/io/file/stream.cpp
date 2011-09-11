
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <string.h>
#include "stream.h"
#include "../../core/system/windows.hdr.h"
#include "../../core/string.h"
#include "../../core/string/wstring.h"

#ifndef YUNI_OS_WINDOWS
// lock
# include <sys/file.h>
#endif


namespace Yuni
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

	Stream::HandleType Stream::OpenFileOnWindows(const char* filename, const int mode)
	{
		Private::WString<> wfilenm(filename);
		if (wfilenm.empty())
			return NULL;
		FILE* f;
		# ifdef YUNI_OS_MSVC
		if (0 != _wfopen_s(&f, wfilenm.c_str(), OpenMode::ToWCString(mode)))
			return NULL;
		# else
		f = _wfopen(wfilenm.c_str(), OpenMode::ToWCString(mode));
		# endif
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



	bool Stream::lockShared()
	{
		# ifndef YUNI_OS_WINDOWS
		return pFd ? (0 == flock(fileno(pFd), LOCK_SH)) : false;
		# else
		// warning The implementation is missing on Windows (#346)
		return false;
		# endif
	}


	bool Stream::lockExclusive()
	{
		# ifndef YUNI_OS_WINDOWS
		return pFd ? (0 == flock(fileno(pFd), LOCK_EX)) : false;
		# else
		// warning The implementation is missing on Windows (#346)
		return false;
		# endif
	}


	void Stream::unlock()
	{
		# ifndef YUNI_OS_WINDOWS
		if (pFd)
			flock(fileno(pFd), LOCK_UN);
		# else
		// warning The implementation is missing on Windows (#346)
		# endif
	}




} // namespace File
} // namespace IO
} // namespace Yuni

