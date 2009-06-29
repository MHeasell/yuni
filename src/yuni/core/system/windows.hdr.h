#ifndef __YUNI_SYSTEM_WINDOWS_HEADERS_H__
# define __YUNI_SYSTEM_WINDOWS_HEADERS_H__


# include "../../yuni.h"

# ifdef YUNI_OS_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN 1
#	endif
#	include <windows.h>
#	include <winsock2.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <time.h>
# endif


// On some compiler, the macro min() and max() are defined... (Visual Studio for example...)
# ifdef min
#   undef min
# endif
# ifdef max
#   undef max
# endif


#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};

// Define gettimeofday. This is posix, but Windows does not provide it.
// Yes, it provides an equivalent, but hey, let's not propagate #ifdefs everywhere.
static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME ft;
	unsigned __int64 tmpRes = 0;
	static int tzFlag;
 
	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);
 
		tmpRes |= ft.dwHighDateTime;
		tmpRes <<= 32;
		tmpRes |= ft.dwLowDateTime;
 
		/*converting file time to unix epoch*/
		tmpRes -= DELTA_EPOCH_IN_MICROSECS; 
		tmpRes /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpRes / 1000000UL);
		tv->tv_usec = (long)(tmpRes % 1000000UL);
	}
 
	if (NULL != tz)
	{
		if (!tzFlag)
		{
			_tzset();
			tzFlag++;
		}

		long newTZ;
		_get_timezone(&newTZ);
		tz->tz_minuteswest = newTZ / 60;
		int dayLight;
		_get_daylight(&dayLight);
		tz->tz_dsttime = dayLight;
	}
 
	return 0;
}

#endif // __YUNI_SYSTEM_WINDOWS_HEADERS_H__
