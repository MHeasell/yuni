
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
		pTitle = title;
	}


	template<typename StringT>
	inline Window::Window(const StringT& newTitle, float width, float height)
		:IControlContainer(width, height),
		pClosing(false)
	{
		pTitle = newTitle;
	}


	template<typename StringT>
	inline Window::Window(const StringT& newTitle, float x, float y, float width,
		float height)
		:IControlContainer(x, y, width, height),
		pClosing(false)
	{
		pTitle = newTitle;
	}

	template<typename StringT, typename NumberT>
	inline Window::Window(const StringT& newTitle, const Point2D<NumberT>& pos, float width,
		float height)
		:IControlContainer(pos, width, height),
		pClosing(false)
	{
		pTitle = newTitle;
	}

	inline Window::~Window()
	{
		destroyBoundEvents();
	}


	template<typename StringT>
	inline void Window::title(const StringT& newTitle)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		// Resetting with the new value
		pTitle = newTitle;
	}

	inline void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		pClosing = true;
		// TODO: Send an event !
	}

	inline bool Window::closing() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pClosing;
	}


} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_WINDOW_HXX__
