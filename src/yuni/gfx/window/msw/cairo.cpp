
#include "../../api/cairo.h"
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Window
{


	bool CairoMSW::initialize()
	{
		IMSWindows::initialize();
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)pUIWnd->width(),
			(unsigned int)pUIWnd->height());
		Surface::Cairo::initialize();
		return true;
	}


	inline void CairoMSW::close()
	{}


	void CairoMSW::resize(float width, float height)
	{
		IMSWindows::resize(width, height);
		release();
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)width,
			(unsigned int)height);
		pContext = cairo_create(pSurface);
		Surface::Cairo::resize(width, height);
	}



} // namespace Window
} // namespace Gfx
} // namespace Yuni
