
#include "factory.h"

# ifdef YUNI_OS_MAC
	// TODO: Write window creation for Cocoa. For the moment do nothing
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
