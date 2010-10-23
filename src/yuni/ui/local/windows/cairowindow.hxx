
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

	inline CairoWindow::CairoWindow(Yuni::UI::Window* source, unsigned int bitDepth, bool fullScreen)
		: IWinGDIWindow(source, bitDepth, fullScreen)
	{
		pWindowClassName = "Cairo";
	}


	inline CairoWindow::~CairoWindow()
	{}


	inline bool CairoWindow::refresh()
	{
		cairo_paint(pContext);
		return true;
	}


	inline void CairoWindow::close()
	{
		destroyBoundEvents();
	}



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
