
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


	inline void CairoWindow::close()
	{
		destroyBoundEvents();
		IWinGDIWindow::close();
	}



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
