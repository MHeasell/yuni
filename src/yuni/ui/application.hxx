#ifndef __YUNI_UI_APPLICATION_HXX__
# define __YUNI_UI_APPLICATION_HXX__


namespace Yuni
{
namespace UI
{


	template<class StringT>
	inline Application::Application(const StringT& name)
		:pName(name)
	{
		initialize();
	}


	inline Application::Application()
	{
		initialize();
	}


	inline Application::~Application()
	{
		quit();
	}


	inline const GUID& Application::guid() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pGUID;
	}


	inline const String& Application::name() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return pName;
	}


	inline void Application::add(const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
		}
	}


	inline Application& Application::operator += (const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
		}
		return *this;
	}


	inline Application& Application::operator += (Window* wnd)
	{
		if (wnd)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
		}
		return *this;
	}


	inline Application& Application::operator << (const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
		}
		return *this;
	}


	inline Application& Application::operator << (Window* wnd)
	{
		if (wnd)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
		}
		return *this;
	}


	inline void Application::remove(IComponent::ID id)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		pWindows.erase(id);
	}


	inline void Application::remove(const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows.erase(wnd->id());
		}
	}


	inline Application& Application::operator -= (IComponent::ID id)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		pWindows.erase(id);
		return *this;
	}


	inline Application& Application::operator -= (Window* wnd)
	{
		if (wnd)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows.erase(wnd->id());
		}
		return *this;
	}


	inline Application& Application::operator -= (const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows.erase(wnd->id());
		}
		return *this;
	}




} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_HXX__
