#ifndef __YUNI_GFX_WINDOW_OPENGLX11_H__
# define __YUNI_GFX_WINDOW_OPENGLX11_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11

#	include "x11yuni.h"
#	include "../window.h"
#	include "../../surface/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief Specialized window implementation for GLX (OpenGL-X11)
	*/
	class OpenGLX11: public IWindow, public Surface::OpenGL
	{
	public:
		OpenGLX11(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			:IWindow(source, bitDepth, fullScreen)
		{}

		virtual bool initialize();

		virtual void close();

		virtual void resize(float width, float height)
		{
			IWindow::resize(width, height);
			Surface::OpenGL::resize(width, height);
		}

		virtual Surface::OpenGL* surface() { return this; }

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;

		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

		virtual bool pollEvents();

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh() { return true; }

		/*!
		** \brief Swap the backbuffer to screen
		*/
		virtual void blitWL();

		virtual void onInternalTitleChangedWL();

	private:
		//! Connection to a X11 Server through TCP or DECnet communications protocols
		Display* pDisplay;
		int pScreen;
		::Window pWindow;
		GLXContext pContext;
		XSetWindowAttributes pAttr;
		XWindowAttributes pWndAttr;
		XEvent pXEvent;

	}; // class OpenGLX11




} // namespace Window
} // namespace Gfx
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_GFX_WINDOW_OPENGLX11_H__
