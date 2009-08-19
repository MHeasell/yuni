#ifndef __YUNI_GFX_WINDOW_FACTORY__
# define __YUNI_GFX_WINDOW_FACTORY__

# include "window.h"

namespace Yuni
{
namespace Gfx
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
# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
		static AWindow* CreateDX9Window(const String& title, unsigned int width, unsigned int height,
			unsigned int bits, bool fullScreen);
# endif


	private:
		Factory() {}
		Factory(const Factory&) {}

	}; // class Factory




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_FACTORY__
