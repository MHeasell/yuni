#ifndef __YUNI_GFX_WINDOW_CAIRO_X11_H__
# define __YUNI_GFX_WINDOW_CAIRO_X11_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11
#	include "x11yuni.h"
#	include "../window.h"
#	include "../../../gfx/surface/cairo.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace X11
{


	/*!
	** \brief X11-specific window, using a Cairo surface to render
	*/
	class CairoWindow: public IWindow, public Yuni::Gfx::Surface::Cairo
	{
	public:
		//! The Threading Policy
		typedef IWindow::ThreadingPolicy ThreadingPolicy;

	public:
		CairoWindow(Yuni::UI::Window* source, unsigned int bitDepth, bool fullScreen);
		virtual ~CairoWindow();

		virtual bool initialize();
		virtual void close();
		virtual void resize(float width, float height);
		virtual Yuni::Gfx::Surface::Cairo* surface2D() { return this; }

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh();

	}; // class CairoWindow



} // namespace X11
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# include "cairowindow.hxx"


# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_PRIVATE_UI_LOCAL_CAIROWINDOW_H__
