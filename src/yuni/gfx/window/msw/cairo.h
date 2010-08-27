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
	class CairoMSW: public AMSWindows, public Surface::Cairo
	{
	public:
		//! The Threading Policy
		typedef AMSWindows::ThreadingPolicy ThreadingPolicy;

	public:
		CairoMSW(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AMSWindows(title, width, height, bitDepth, fullScreen)
		{
			pWindowClassName = "Cairo";
		}

		virtual bool initialize();
		virtual void close();
		virtual void resize(unsigned int width, unsigned int height);
		virtual Surface::Cairo* surface() const { return const_cast<CairoMSW*>(this); }

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

	private:
		HDC pHDC;

	}; // class CairoMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_CAIRO_MSW_H__
