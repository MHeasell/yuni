#ifndef __YUNI_GFX3D_WINDOW_OPENGLX11_H__
# define __YUNI_GFX3D_WINDOW_OPENGLX11_H__

# include "../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11

#	include "x11yuni.h"
#	include "../window/opengl.h"


namespace Yuni
{
namespace Gfx3D
{
namespace Window
{


	/*!
	** \brief Specialized window implementation for GLX (OpenGL-X11)
	*/
	class OpenGLX11: public Yuni::Gfx3D::Window::OpenGL
	{
	public:
		OpenGLX11(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:OpenGL(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize();
		virtual void close();
		virtual void blit();

	private:
		//! Connection to a X11 Server through TCP or DECnet communications protocols
		Display* pDisplay;
		int pScreen;
		::Window pWindow;
		GLXContext pContext;
		XSetWindowAttributes pAttr;
		XWindowAttributes pWndAttr;

	}; // class WindowGLX




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_GFX3D_WINDOW_OPENGLX11_H__
