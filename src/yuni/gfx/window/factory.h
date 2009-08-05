
#ifndef __YUNI_GFX3D_WINDOW_FACTORY__
# define __YUNI_GFX3D_WINDOW_FACTORY__

# include "window.h"

namespace Yuni
{
namespace Gfx3D
{
namespace Window
{

	class Factory
	{
	public:
		static AWindow* CreateGLWindow(const char* title, unsigned int width, unsigned int height,
			unsigned int bitDepth, bool fullScreen);

	private:
		Factory() {}
		Factory(const Factory&) {}

	}; // Factory

} // Window
} // Gfx3D
} // Yuni

#endif // __YUNI_GFX3D_WINDOW_FACTORY__
