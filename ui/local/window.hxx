#ifndef __YUNI_PRIVATE_LOCAL_UI_WINDOW_HXX__
# define __YUNI_PRIVATE_LOCAL_UI_WINDOW_HXX__


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{


	inline IWindow::IWindow(const Yuni::UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
		: pUIWnd(source), pBitDepth(bitDepth), pFullScreen(fullScreen)
	{
	}


	inline IWindow::~IWindow()
	{
		destroyBoundEvents();
	}


	inline bool IWindow::closing() const
	{
		return pUIWnd->closing();
	}



} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_LOCAL_UI_WINDOW_HXX__
