
#ifndef __YUNI_UI_WINDOW_HXX__
# define __YUNI_UI_WINDOW_HXX__

namespace Yuni
{
namespace UI
{


	template<typename StringT>
	inline Window::Window(const StringT& title)
		: pClosing(false)
	{
		title(title);
	}

	template<typename StringT>
	inline Window::Window(const StringT& newTitle, size_t width, size_t height)
		: IComponent(width, height), pClosing(false)
	{
		title(newTitle);
	}

	template<typename StringT, typename NumberT, typename NumberT2>
	inline Window::Window(const StringT& newTitle, NumberT x, NumberT2 y, size_t width, size_t height)
		: IComponent(x, y, width, height), pClosing(false)
	{
		title(newTitle);
	}

	template<typename StringT, typename NumberT>
	inline Window::Window(const StringT& newTitle, const Point2D<NumberT>& pos, size_t width, size_t height)
		: IComponent(pos, width, height), pClosing(false)
	{
		title(newTitle);
	}

	inline Window::~Window()
	{
		destroyBoundEvents();
	}


	template<typename StringT>
	inline void Window::title(const StringT& newTitle)
	{
		// Resetting with the new value
		pTitle = newTitle;
		pTitleModified = true;
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_WINDOW_HXX__
