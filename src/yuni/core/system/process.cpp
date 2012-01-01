
#include "../../yuni.h"
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

	unsigned int ProcessID()
	{
		return (unsigned int) YUNI_OS_GETPID();
	}



} // namespace Yuni
