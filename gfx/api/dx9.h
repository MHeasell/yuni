#ifndef __YUNI_GFX_API_DIRECTX9_H__
# define __YUNI_GFX_API_DIRECTX9_H__

# include "../../yuni.h"

# if defined(YUNI_OS_WINDOWS) && defined(YUNI_USE_DIRECTX)
#	include "../../core/system/windows.hdr.h"
#	if defined __GNUC__
// Disable warnings for DirectX headers included with gcc (mingw)
#		pragma GCC system_header
#	endif
#	include <d3d9.h>
#	include <d3dx9.h>
# endif // YUNI_OS_WINDOWS

#endif // __YUNI_GFX_API_DIRECTX9_H__
