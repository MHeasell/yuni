#ifndef __YUNI_GFX_WINDOW_WINDOW_HXX__
# define __YUNI_GFX_WINDOW_WINDOW_HXX__



namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline AWindow::AWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
		:pTitle(title), pWidth(width), pHeight(height), pBitDepth(bitDepth), pFullScreen(fullScreen), pClosing(false)
	{}


	inline AWindow::~AWindow()
	{
		destroyBoundEvents();
	}


	inline bool AWindow::closing() const
	{
		return pClosing;
	}


	inline bool AWindow::verticalSync() const
	{
		return true;
	}


	inline bool AWindow::verticalSync(bool)
	{
		return false;
	}


	template<typename C>
	inline void AWindow::title(const C& newTitle)
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
