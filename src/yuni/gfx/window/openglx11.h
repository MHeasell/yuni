#ifndef __YUNI_GFX3D_WINDOW_OPENGLX11_H__
# define __YUNI_GFX3D_WINDOW_OPENGLX11_H__

# include "../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11

#	include "x11yuni.h"
#	include "../window/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief Specialized window implementation for GLX (OpenGL-X11)
	*/
	class OpenGLX11: public AWindow, public AOpenGL
	{
	public:
		OpenGLX11(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AWindow(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize();
		virtual void close();
		virtual void blit();
		virtual void resize(unsigned int width, unsigned int height)
		{
			AOpenGL::resize(width, height);
		}

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

		virtual void onTitleChanged();

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
} // namespace Gfx
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_GFX3D_WINDOW_OPENGLX11_H__
