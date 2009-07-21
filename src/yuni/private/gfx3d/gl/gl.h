#ifndef __YUNI_PRIVATE_GFX_OPENGL_H__
# define __YUNI_PRIVATE_GFX_OPENGL_H__

# include "../../../yuni.h"

# ifdef YUNI_OS_MAC
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
# endif // YUNI_OS_MAC

#endif // __YUNI_PRIVATE_GFX_OPENGL_H__
