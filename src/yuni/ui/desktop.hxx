#ifndef __YUNI_UI_DESKTOP_HXX__
# define __YUNI_UI_DESKTOP_HXX__


namespace Yuni
{
namespace UI
{


	inline void Desktop::add(Application::Ptr& app)
	{
		pApps[app->id()] = app;
	}


	inline Desktop& Desktop::operator += (Application::Ptr& app)
	{
		pApps[app->id()] = app;
		return *this;
	}


	inline Desktop& Desktop::operator << (Application::Ptr& app)
	{
		pApps[app->id()] = app;
		return *this;
	}


	inline void Desktop::remove(const String& id)
	{
		pApps.erase(id);
	}


	inline void Desktop::remove(Application::Ptr& app)
	{
		pApps.erase(app->id());
	}


	inline Desktop& Desktop::operator -= (const String& id)
	{
		pApps.erase(id);
		return *this;
	}


	inline Desktop& Desktop::operator -= (Application::Ptr& app)
	{
		pApps.erase(app->id());
		return *this;
	}



} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_DESKTOP_HXX__
