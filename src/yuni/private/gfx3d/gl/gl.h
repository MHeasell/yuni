#ifndef __YUNI_PRIVATE_GFX_OPENGL_H__
# define __YUNI_PRIVATE_GFX_OPENGL_H__

# include "../../../yuni.h"

# ifdef YUNI_OS_MAC
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  ifdef YUNI_OS_WINDOWS
#   include "../../../core/system/windows.hdr.h"
#  endif // YUNI_OS_WINDOWS
#  include <GL/gl.h>
#  include <GL/glu.h>
# endif // YUNI_OS_MAC

#endif // __YUNI_PRIVATE_GFX_OPENGL_H__
