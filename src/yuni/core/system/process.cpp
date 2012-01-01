
#include "process.h"
#ifndef YUNI_OS_WINDOWS
#	ifndef YUNI_OS_HAIKU
#		include <sys/errno.h>
#	endif
#	include <unistd.h>
#else
#	include "windows.hdr.h"
#endif


#if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
#	define YUNI_OS_GETPID  _getpid
#else
#	define YUNI_OS_GETPID   getpid
#endif



namespace Yuni
{

	uint64 ProcessID()
	{
		return (uint64) YUNI_OS_GETPID();
	}



} // namespace Yuni
