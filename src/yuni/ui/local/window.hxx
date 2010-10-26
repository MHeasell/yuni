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
		: pUIWnd(source), pBitDepth(bitDepth), pFullScreen(fullScreen), pClosing(false)
	{
	}


	inline IWindow::~IWindow()
	{
		destroyBoundEvents();
	}


	inline bool IWindow::closing() const
	{
		return pClosing;
	}

	inline void IWindow::resize(float width, float height)
	{
		pUIWnd->resize(width, height);
	}


} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_LOCAL_UI_WINDOW_HXX__
