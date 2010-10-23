
#include "cairowindow.h"

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


	bool CairoWindow::initialize()
	{
		IWindow::initialize();
		/*
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)pUIWnd->width(),
			(unsigned int)pUIWnd->height());
		*/
		Yuni::Gfx::Surface::Cairo::initialize();
		return true;
	}


	void CairoWindow::resize(float width, float height)
	{
		IWindow::resize(width, height);
		release();
		/*
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
			CAIRO_FORMAT_ARGB32, (unsigned int)width,
			(unsigned int)height);
		pContext = cairo_create(pSurface);
		*/
		Yuni::Gfx::Surface::Cairo::resize(width, height);
	}



} // namespace X11
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
