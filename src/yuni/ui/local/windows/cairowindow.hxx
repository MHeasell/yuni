
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
