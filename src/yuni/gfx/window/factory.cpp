
#include "factory.h"

# ifdef YUNI_OS_MAC
#  include "openglx11.h"
	// TODO: Write window creation for Cocoa instead of X11
	//#	include "openglcocoa.hxx"
# else
# 	ifdef YUNI_OS_WINDOWS
#		include "openglmsw.h"
#   else
#		ifdef YUNI_OS_UNIX
#			include "openglx11.h"
#		else
#			error No window creation available for your platform!
#		endif
# 	endif
# endif
