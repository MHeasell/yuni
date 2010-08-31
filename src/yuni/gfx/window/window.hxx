#ifndef __YUNI_GFX_WINDOW_WINDOW_HXX__
# define __YUNI_GFX_WINDOW_WINDOW_HXX__


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline IWindow::IWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
		: IComponent(width, height), pTitle(title), pBitDepth(bitDepth), pFullScreen(fullScreen), pClosing(false), pUI(NULL)
	{}


	inline IWindow::~IWindow()
	{
		destroyBoundEvents();
	}


	inline bool IWindow::closing() const
	{
		return pClosing;
	}

	template<typename C>
	inline void IWindow::title(const C& newTitle)
	{
		// Resetting with the new value
		pTitle = newTitle;
		// Updating the change according to the real implementation
		onInternalTitleChangedWL();
	}



} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_WINDOW_HXX__
