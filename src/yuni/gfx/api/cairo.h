#ifndef __YUNI_GFX_API_CAIRO_H__
# define __YUNI_GFX_API_CAIRO_H__

# include "../../yuni.h"

// Including pangocairo is enough, it includes both pango.h and cairo.h
# include <pango/pangocairo.h>

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include <cairo-win32.h>
# endif


#endif // __YUNI_GFX_API_CAIRO_H__
