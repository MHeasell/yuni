
#ifndef __YUNI_GFX3D_WINDOW_FACTORY__
# define __YUNI_GFX3D_WINDOW_FACTORY__

# include "window.h"

namespace Yuni
{
namespace Gfx3D
{
namespace Window
{
	/*!
	** \brief Window factory: manages API-dependent window creation.
	**
	** This is not a factory design pattern stricto sensu. It only collects static methods.
	*/
	class Factory
	{
	public:
		static AWindow* CreateGLWindow(const String& title, unsigned int width, unsigned int height,
			unsigned int bitDepth, bool fullScreen);

	private:
		Factory() {}
		Factory(const Factory&) {}

	}; // Factory

} // Window
} // Gfx3D
} // Yuni

#endif // __YUNI_GFX3D_WINDOW_FACTORY__
