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


	inline const Application::GUID& Application::guid() const
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
			reconnectOneWindowWL(wnd);
		}
	}


	inline Application& Application::operator += (const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
			reconnectOneWindowWL(wnd);
		}
		return *this;
	}


	inline Application& Application::operator += (Window* wnd)
	{
		if (wnd)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
			reconnectOneWindowWL(wnd);
		}
		return *this;
	}


	inline Application& Application::operator << (const Window::Ptr& wnd)
	{
		if (!(!wnd))
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
			reconnectOneWindowWL(wnd);
		}
		return *this;
	}


	inline Application& Application::operator << (Window* wnd)
	{
		if (wnd)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWindows[wnd->id()] = wnd;
			reconnectOneWindowWL(wnd);
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


	inline void Application::reconnect()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		reconnectWL();
	}


	inline void Application::disconnect()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		disconnectWL();
	}


	inline void Application::showWindow(Window::Ptr window)
	{
		if (onApplicationShowWindow)
		{
			(*onApplicationShowWindow)(pGUID, window);
		}
	}


	inline void Application::hideWindow(const IComponent::ID& windowID)
	{
		if (onApplicationHideWindow)
			(*onApplicationHideWindow)(pGUID, windowID);
	}


	inline void Application::closeWindow(const IComponent::ID& windowID)
	{
		if (onApplicationCloseWindow)
			(*onApplicationCloseWindow)(pGUID, windowID);
	}


	inline void Application::showComponent(IComponent::Ptr component)
	{
		if (onApplicationShowComponent)
			(*onApplicationShowComponent)(pGUID, component);
	}


	inline void Application::hideComponent(const IComponent::ID& componentID)
	{
		if (onApplicationHideComponent)
			(*onApplicationHideComponent)(pGUID, componentID);
	}


	inline void Application::updateComponent(const IComponent::ID& componentID)
	{
		if (onApplicationUpdateComponent)
			(*onApplicationUpdateComponent)(pGUID, componentID);
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_HXX__
