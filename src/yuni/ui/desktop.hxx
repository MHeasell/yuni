#ifndef __YUNI_UI_DESKTOP_HXX__
# define __YUNI_UI_DESKTOP_HXX__


namespace Yuni
{
namespace UI
{


	inline void Desktop::add(Application::Ptr& app)
	{
		pApps[app->ID()] = app;
	}


	inline Desktop& Desktop::operator += (Application::Ptr& app)
	{
		pApps[app->ID()] = app;
		return *this;
	}


	inline Desktop& Desktop::operator << (Application::Ptr& app)
	{
		pApps[app->ID()] = app;
		return *this;
	}


	inline void Desktop::remove(const String& id)
	{
		pApps.erase(id);
	}


	inline void Desktop::remove(Application::Ptr& app)
	{
		pApps.erase(app->ID());
	}


	inline Desktop& Desktop::operator -= (Application::Ptr& app)
	{
		pApps.erase(app->ID());
		return *this;
	}



} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_DESKTOP_HXX__
