
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

	inline CairoWindow::CairoWindow(const Yuni::UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
		: IWinGDIWindow(source, bitDepth, fullScreen)
	{
		pWindowClassName = "Cairo";
	}


	inline CairoWindow::~CairoWindow()
	{}


	inline bool CairoWindow::refresh()
	{
		release();
		pSurface = cairo_win32_printing_surface_create(GetDC(pHWnd));
// 		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWnd),
// 			CAIRO_FORMAT_RGB24, (unsigned int)pUIWnd->width(),
// 			(unsigned int)pUIWnd->height());
		assert(cairo_surface_status(pSurface) == CAIRO_STATUS_SUCCESS && "Cairo surface creation failed !");
		return Yuni::Gfx::Surface::Cairo::refresh();
	}


	inline void CairoWindow::close()
	{
		release();
		destroyBoundEvents();
		IWinGDIWindow::close();
	}



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
