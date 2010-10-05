#ifndef __YUNI_UI_APPLICATION_HXX__
# define __YUNI_UI_APPLICATION_HXX__


namespace Yuni
{
namespace UI
{


	template<typename StringT, typename StringT2>
	inline Application::Application(const StringT& id, const StringT2& name)
		: pID(id), pName(name)
	{}


	inline const Application::StaticString& Application::id()
	{
		return pID;
	}


	inline const Application::StaticString& Application::name()
	{
		return pName;
	}


	inline void Application::add(Window::Ptr& wnd)
	{
		pWindows[wnd->id()] = wnd;
	}


	inline Application& Application::operator += (Window::Ptr& wnd)
	{
		pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline Application& Application::operator << (Window::Ptr& wnd)
	{
		pWindows[wnd->id()] = wnd;
		return *this;
	}


	inline void Application::remove(IComponent::ID id)
	{
		pWindows.erase(id);
	}


	inline void Application::remove(Window::Ptr& app)
	{
		pWindows.erase(app->id());
	}


	inline Application& Application::operator -= (IComponent::ID id)
	{
		pWindows.erase(id);
		return *this;
	}


	inline Application& Application::operator -= (Window::Ptr& app)
	{
		pWindows.erase(app->id());
		return *this;
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_HXX__
