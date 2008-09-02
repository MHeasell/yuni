#ifndef __YUNI_SYSTEM_WINDOWS_HEADERS_H__
# define __YUNI_SYSTEM_WINDOWS_HEADERS_H__


# include "../yuni.h"

# ifdef YUNI_OS_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN 1
#	endif
#	include <windows.h>
# endif


#endif // __YUNI_SYSTEM_WINDOWS_HEADERS_H__
