
#ifndef __YUNI_GFX3D_WINDOW_OPENGLX11_H__
# define __YUNI_GFX3D_WINDOW_OPENGLX11_H__

#include <GL/glx.h>
#include "opengl.h"

namespace Yuni
{
namespace Gfx3D
{
namespace Window
{

	/*!
	** \brief Specialized window implementation for GLX (OpenGL-X11)
	*/
	class OpenGLX11: public OpenGL
	{
	public:
		OpenGLX11(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:OpenGL(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize();
		virtual void close();
		virtual void blit();

	private:
		Display* pDisplay;
		int pScreen;
		Window pWindow;
		GLXContext pContext;
		XSetWindowAttributes pAttr;
		XWindowAttributes pWndAttr;

	}; // WindowGLX


} // Window
} // Gfx3D
} // Yuni

#include "openglx11.hxx"

#endif // __YUNI_GFX3D_WINDOW_OPENGLX11_H__
