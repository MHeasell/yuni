#ifndef __YUNI_GFX_WINDOW_WINDOW_HXX__
# define __YUNI_GFX_WINDOW_WINDOW_HXX__


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline IWindow::IWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
	{
	}


	inline IWindow::~IWindow()
	{
	}


	inline bool IWindow::closing() const
	{
		return pClosing;
	}


} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_WINDOW_HXX__
