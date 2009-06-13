#ifndef __YUNI_SYSTEM_WINDOWS_HEADERS_H__
# define __YUNI_SYSTEM_WINDOWS_HEADERS_H__


# include "../../yuni.h"

# ifdef YUNI_OS_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN 1
#	endif
#	include <windows.h>

#	include <stdio.h>
#	include <stdlib.h>
# endif


// On some compiler, the macro min() and max() are defined... (Visual Studio for example...)
# ifdef min
#   undef min
# endif
# ifdef max
#   undef max
# endif


#endif // __YUNI_SYSTEM_WINDOWS_HEADERS_H__
