#ifndef __YUNI_GFX_WINDOW_X11_YUNI_H__
# define __YUNI_GFX_WINDOW_X11_YUNI_H__


# include "../../../yuni.h"
# include <GL/glx.h>
# include <X11/extensions/Xrender.h>

// The define None from the X11 headers overlaps with Yuni::None...
# ifdef None
#	undef None
# endif

# define YUNI_X11LIB_NONE  0L


#endif // __YUNI_GFX_WINDOW_X11_YUNI_H__
