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
		return pGUID;
	}


	inline const String& Application::name() const
	{
		return pName;
	}


	inline void Application::add(const Window::Ptr& wnd)
	{
		if (!(!wnd))
			pWindows[wnd->id()] = wnd;
	}


	inline Application& Application::operator += (const Window::Ptr& wnd)
	{
		if (!(!wnd))
			pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline Application& Application::operator += (Window* wnd)
	{
		if (wnd)
			pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline Application& Application::operator << (const Window::Ptr& wnd)
	{
		if (!(!wnd))
			pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline Application& Application::operator << (Window* wnd)
	{
		if (wnd)
			pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline void Application::remove(IComponent::ID id)
	{
		pWindows.erase(id);
	}


	inline void Application::remove(const Window::Ptr& wnd)
	{
		if (!(!wnd))
			pWindows.erase(wnd->id());
	}


	inline Application& Application::operator -= (IComponent::ID id)
	{
		pWindows.erase(id);
		return *this;
	}


	inline Application& Application::operator -= (Window* wnd)
	{
		if (wnd)
			pWindows.erase(wnd->id());
		return *this;
	}


	inline Application& Application::operator -= (const Window::Ptr& wnd)
	{
		if (!(!wnd))
			pWindows.erase(wnd->id());
		return *this;
	}


	inline void Application::updateComponentWL(const IComponent::ID& componentID) const
	{
		if (pDesktop)
			pDesktop->updateComponentWL(componentID);
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_HXX__
