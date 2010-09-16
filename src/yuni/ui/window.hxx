
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
	inline Window::Window(const StringT& newTitle, unsigned int width, unsigned int height)
		: IComponent(width, height), pClosing(false)
	{
		title(newTitle);
	}

	template<typename StringT, typename NumberT, typename NumberT2>
	inline Window::Window(const StringT& newTitle, NumberT x, NumberT2 y, unsigned int width,
		unsigned int height)
		: IComponent(x, y, width, height), pClosing(false)
	{
		title(newTitle);
	}

	template<typename StringT, typename NumberT>
	inline Window::Window(const StringT& newTitle, const Point2D<NumberT>& pos, unsigned int width,
		unsigned int height)
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
