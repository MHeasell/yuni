#ifndef __YUNI_GFX_WINDOW_CAIRO_MSW_H__
# define __YUNI_GFX_WINDOW_CAIRO_MSW_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../../core/system/windows.hdr.h"
#	include "msw.h"
#	include "../../surface/cairo.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Microsoft Windows-specific window, using a Cairo surface to render
	*/
	class CairoMSW: public IMSWindows, public Surface::Cairo
	{
	public:
		//! The Threading Policy
		typedef IMSWindows::ThreadingPolicy ThreadingPolicy;

	public:
		CairoMSW(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			:IMSWindows(source, bitDepth, fullScreen)
		{
			pWindowClassName = "Cairo";
		}

		virtual bool initialize();
		virtual void close();
		virtual void resize(float width, float height);
		virtual Surface::Cairo* surface2D() { return this; }

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh() { return true; }

		virtual void blitWL();

	protected:
		//! The Cairo surface
		cairo_surface_t* pSurface;

	}; // class CairoMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_CAIRO_MSW_H__
