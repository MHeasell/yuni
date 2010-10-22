#ifndef __YUNI_PRIVATE_UI_LOCAL_WINDOWS_CAIROWINDOW_H__
# define __YUNI_PRIVATE_UI_LOCAL_WINDOWS_CAIROWINDOW_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../../core/system/windows.hdr.h"
#	include "wingdiwindow.h"
#	include "../../../gfx/surface/cairo.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace Windows
{


	/*!
	** \brief Microsoft Windows-specific window, using a Cairo surface to render
	*/
	class CairoWindow: public IWinGDIWindow, public Yuni::Gfx::Surface::Cairo
	{
	public:
		//! The Threading Policy
		typedef IWinGDIWindow::ThreadingPolicy ThreadingPolicy;

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

		virtual void blitWL();

	}; // class CairoWindow



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# include "cairowindow.hxx"


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_PRIVATE_UI_LOCAL_WINDOWS_CAIROWINDOW_H__
