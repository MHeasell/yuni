
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

	inline CairoWindow::CairoWindow(Yuni::UI::Window* source, unsigned int bitDepth,
		bool fullScreen)
		: IWindow(source, bitDepth, fullScreen)
	{}


	inline CairoWindow::~CairoWindow()
	{}


	inline void CairoWindow::close()
	{
		destroyBoundEvents();
	}


	inline bool CairoWindow::refresh()
	{
		cairo_paint(pContext);
		return true;
	}



} // namespace X11
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
