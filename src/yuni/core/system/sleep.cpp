
#include "sleep.h"
#if defined(YUNI_OS_WINDOWS)
# include "windows.hdr.h"
#else
# include <unistd.h>
#endif



namespace Yuni
{

	void Sleep(const uint32 seconds)
	{
		# if defined(YUNI_OS_WINDOWS)
		::Sleep(1000 * seconds);
		# else
		::sleep(seconds);
		# endif
	}


	void SleepMilliSeconds(const uint32 milliseconds)
	{
		# if defined(YUNI_OS_WINDOWS)
		::Sleep(milliseconds);
		# else
		::usleep(1000 * milliseconds);
		# endif
	}


} // namespace Yuni

