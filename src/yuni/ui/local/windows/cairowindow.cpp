
#include "../../../gfx/api/cairo.h"
#include "cairowindow.h"

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


	bool CairoWindow::initialize()
	{
		IWinGDIWindow::initialize();
		pSurface = cairo_win32_printing_surface_create(GetDC(pHWnd));
// 		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
// 			CAIRO_FORMAT_ARGB32, (unsigned int)pUIWnd->width(),
// 			(unsigned int)pUIWnd->height());
		assert(cairo_surface_status(pSurface) == CAIRO_STATUS_SUCCESS && "Cairo surface creation failed !");
		Surface::Cairo::initialize();
		return true;
	}


	void CairoWindow::resize(float width, float height)
	{
		IWinGDIWindow::resize(width, height);
		release();
		pSurface = cairo_win32_printing_surface_create(GetDC(pHWnd));
// 		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
// 			CAIRO_FORMAT_ARGB32, (unsigned int)width,
// 			(unsigned int)height);
		assert(cairo_surface_status(pSurface) == CAIRO_STATUS_SUCCESS && "Cairo surface creation failed !");
		Surface::Cairo::resize(width, height);
	}



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
