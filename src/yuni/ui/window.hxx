#ifndef __YUNI_UI_WINDOW_HXX__
# define __YUNI_UI_WINDOW_HXX__


namespace Yuni
{
namespace UI
{


	template<class StringT>
	inline Window::Window(const StringT& title)
		:pTitle(title), pClosing(false)
	{}


	template<class StringT>
	inline Window::Window(const StringT& title, float width, float height)
		:IControlContainer(width, height),
		pTitle(title),
		pClosing(false)
	{}


	template<class StringT>
	inline Window::Window(const StringT& newTitle, float x, float y, float width,
		float height)
		:IControlContainer(x, y, width, height),
		pTitle(title),
		pClosing(false)
	{}


	template<class StringT, class T>
	inline Window::Window(const StringT& title, const Point2D<T>& pos, float width, float height)
		:IControlContainer(pos, width, height),
		pTitle(title),
		pClosing(false)
	{}


	inline Window::~Window()
	{
		destroyBoundEvents();
	}


	inline String Window::title() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pTitle;
	}


	template<class StringT>
	inline void Window::title(const StringT& newTitle)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		// Resetting with the new value
		pTitle = newTitle;
	}


	template<class StringT>
	inline void Window::titleWL(const StringT& newTitle)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		// Resetting with the new value (without lock)
		pTitle = newTitle;
	}



	inline bool Window::closing() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pClosing;
	}


	inline bool Window::pollEvents()
	{
		return false;
	}


	inline void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
		{
			pClosing = true;
			onClose();
		}
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_WINDOW_HXX__
