#ifndef __YUNI_SYSTEM_WINDOWS_GETTIMEOFDAY_H__
# define __YUNI_SYSTEM_WINDOWS_GETTIMEOFDAY_H__

# include "../../../yuni.h"

# ifdef YUNI_OS_WINDOWS
#	include "../windows.hdr.h"

# ifndef YUNI_OS_MSVC

#   include <sys/time.h>

# else // YUNI_OS_MSVC

#   ifdef YUNI_OS_WINDOWS
#	    include <time.h>
#	    if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#		    define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#	    else
#		    define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#	    endif
#   endif

namespace Yuni
{

	struct timezone 
	{
		int  tz_minuteswest; // minutes W of Greenwich
		int  tz_dsttime;     // type of dst correction
	};

	typedef struct timeval
	{
		long tv_sec;
		long tv_usec;
	} timeval;

	int gettimeofday(struct timeval *tv, struct timezone *tz);

} // namespace Yuni


#   endif // YUNI_OS_MSVC
# endif // YUNI_OS_WINDOWS

#endif // __YUNI_SYSTEM_WINDOWS_GETTIMEOFDAY_H__
