#ifndef __YUNI_PRIVATE_GFX_IRRLICHT_H__
# define __YUNI_PRIVATE_GFX_IRRLICHT_H__

# include "../../../yuni.h"


# if defined(YUNI_OS_GCC) && YUNI_OS_GCC_VERSION >= 40200  // >= 4.2.0
/*!
** \brief Ignore warnings from the Irrlicht Engine
*/
#	define YUNI_IGNORE_GCC_WARNINGS
# endif


# ifdef YUNI_IGNORE_GCC_WARNINGS
#	pragma GCC diagnostic ignored "-Wunused-parameter"
#	pragma GCC diagnostic ignored "-Wunused-variable"
#	pragma GCC diagnostic ignored "-Wshadow"
#	pragma GCC diagnostic ignored "-Woverloaded-virtual"
# endif

//# include <irrlicht.h>
# include "../../../../../devpacks/irrlicht/1.4.2/r2/i386/vs8/include/irrlicht.h"

// Restore all warnings
# ifdef YUNI_IGNORE_GCC_WARNINGS
#	pragma GCC diagnostic warning "-Wunused-parameter"
#	pragma GCC diagnostic warning "-Wunused-variable"
#	pragma GCC diagnostic warning "-Wshadow"
#	pragma GCC diagnostic warning "-Woverloaded-virtual"
# endif


# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
#	pragma comment(lib, "Irrlicht.lib")
# endif


#endif // __YUNI_PRIVATE_GFX_IRRLICHT_H__
