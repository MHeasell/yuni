#ifndef __YUNI_GFX_WINDOW_CAIRO_X11_H__
# define __YUNI_GFX_WINDOW_CAIRO_X11_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11
#	include "x11yuni.h"
#	include "../window.h"
#	include "../../surface/cairo.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief X11-specific window, using a Cairo surface to render
	*/
	class CairoX11: public IWindow, public Surface::Cairo
	{
	public:
		//! The Threading Policy
		typedef IWindow::ThreadingPolicy ThreadingPolicy;

	public:
		CairoX11(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			:IWindow(source, bitDepth, fullScreen)
		{}

		virtual ~CairoX11() {}

		virtual bool initialize();
		virtual void close();
		virtual void resize(float width, float height);
		virtual Surface::Cairo* surface2D() { return this; }

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh();

		virtual void blitWL();

	}; // class CairoX11




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# include "cairo.hxx"


# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_GFX_WINDOW_CAIRO_X11_H__
