
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#undef __STRICT_ANSI__

#include <string.h>
#include "stream.h"
#include "../../core/string.h"
#include "../../core/string/wstring.h"

#ifdef YUNI_OS_WINDOWS
# include "../../core/system/windows.hdr.h"
# include <io.h>
# include <stdio.h>    // _fileno
#else
# include <sys/file.h> // lock
#endif

#ifndef YUNI_OS_MSVC
# include <unistd.h>   // ftruncate
#endif

#ifdef YUNI_OS_WINDOWS
# define FILENO(X)  _fileno(X)
#else
# define FILENO(X)  fileno(X)
#endif



namespace Yuni
{
namespace IO
{
namespace File
{


	# ifdef YUNI_OS_WINDOWS

	static Stream::HandleType OpenFileOnWindows(const AnyString& filename, int mode)
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



	Stream::Stream(const Stream&) :
		pFd(nullptr)
	{
		// Do nothing
	}


	Stream::Stream(const AnyString& filename, int mode) :
		pFd(nullptr)
	{
		open(filename, mode);
	}



	bool Stream::open(const AnyString& filename, int mode)
	{
		// Close the file if already opened
		if (pFd)
			(void)::fclose(pFd);

		# ifdef YUNI_OS_WINDOWS
		pFd = OpenFileOnWindows(filename, mode);
		# else
		// It is mandatory to open file with the flag O_CLOEXEC to avoid race
		// conditions with fork
		// fopen should used O_CLOEXEC as one of the option. However, at the current
		// state, not all operating systems do that.
		// So we have to do it by ourselves with open and fdopen.
		/*int flag = O_CLOEXEC;
		if (0 != (mode & OpenMode::read) && 0 != (mode & OpenMode::write))
			flag |= O_RDWR;
		else if (0 != (mode & OpenMode::read))
			flag |= O_RDONLY;
		else if (0 != (mode & OpenMode::write))
			flag |= O_WRONLY;

		if (0 != (mode & OpenMode::truncate))
			flag |= O_TRUNC;
		else if (0 != (mode & OpenMode::append))
			flag |= O_APPEND;

		if (0 != (mode & ~OpenMode::read))
			flag |= O_CREAT;

		int fd = ::open(filename.c_str(), flag);
		if (fd < 0) // error
			pFd = nullptr;
		else
			pFd = ::fdopen(fd, OpenMode::ToCString(mode));*/
		pFd = ::fopen(filename.c_str(), OpenMode::ToCString(mode));
		# endif

		return (NULL != pFd);
	}



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
		return pFd ? (0 == flock(FILENO(pFd), LOCK_SH)) : false;
		# else
		// warning The implementation is missing on Windows (#346)
		assert("Stream::lock: the implementation is missing on Windows, see ticket #346");
		return false;
		# endif
	}


	bool Stream::lockExclusive()
	{
		# ifndef YUNI_OS_WINDOWS
		return pFd ? (0 == flock(FILENO(pFd), LOCK_EX)) : false;
		# else
		// warning The implementation is missing on Windows (#346)
		assert("Stream::lock: the implementation is missing on Windows, see ticket #346");
		return false;
		# endif
	}


	void Stream::unlock()
	{
		# ifndef YUNI_OS_WINDOWS
		if (pFd)
			flock(FILENO(pFd), LOCK_UN);
		# else
		// warning The implementation is missing on Windows (#346)
		assert("Stream::lock: the implementation is missing on Windows, see ticket #346");
		# endif
	}


	bool Stream::truncate(uint64 size)
	{
		if (pFd)
		{
			# ifndef YUNI_OS_MSVC
			return (0 == ::ftruncate(FILENO(pFd), (off_t) size));
			# else
			return (0 == _chsize_s(FILENO(pFd), (sint64) size));
			# endif
		}
		return false;
	}




} // namespace File
} // namespace IO
} // namespace Yuni

