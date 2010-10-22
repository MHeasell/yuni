
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Window
{


	bool CairoX11::initialize()
	{
		IWindow::initialize();
		/*
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)pUIWnd->width(),
			(unsigned int)pUIWnd->height());
		*/
		Surface::Cairo::initialize();
		return true;
	}


	inline void CairoX11::close()
	{
		destroyBoundEvents();
	}


	void CairoX11::resize(float width, float height)
	{
		IWindow::resize(width, height);
		release();
		/*
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)width,
			(unsigned int)height);
		pContext = cairo_create(pSurface);
		*/
		Surface::Cairo::resize(width, height);
	}



} // namespace Window
} // namespace Gfx
} // namespace Yuni
