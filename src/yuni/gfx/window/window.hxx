#ifndef __YUNI_GFX_WINDOW_WINDOW_HXX__
# define __YUNI_GFX_WINDOW_WINDOW_HXX__


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline IWindow::IWindow(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
		: pUIWnd(source), pBitDepth(bitDepth), pFullScreen(fullScreen), pClosing(false)
	{
	}


	inline IWindow::~IWindow()
	{
	}


	inline bool IWindow::closing() const
	{
		return pClosing;
	}

	inline void IWindow::resize(float width, float height)
	{
		pUIWnd->resize(width, height);
	}


} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_WINDOW_HXX__
