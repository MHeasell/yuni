#ifndef __YUNI_GFX_API_OPENGL_H__
# define __YUNI_GFX_API_OPENGL_H__

# include "../../yuni.h"

# ifdef YUNI_OS_MAC
#	include <OpenGL/gl.h>
#	include <OpenGL/glu.h>
# else
#	ifdef YUNI_OS_WINDOWS
#		include "../../core/system/windows.hdr.h"
#	endif // YUNI_OS_WINDOWS
#	include <GL/gl.h>
#	include <GL/glu.h>
# endif // YUNI_OS_MAC

#endif // __YUNI_GFX_API_OPENGL_H__
