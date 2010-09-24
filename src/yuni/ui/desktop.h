#ifndef __YUNI_UI_DESKTOP_H__
# define __YUNI_UI_DESKTOP_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "application.h"

namespace Yuni
{
namespace UI
{


	/*!
	** \brief Virtual desktop meant to receive one or several applications
	*/
	class Desktop
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Desktop> Ptr;

	public:
		/*!
		** \brief Main constructor
		*/
		Desktop() {}

		/*!
		** \brief Add an application to this desktop
		*/
		void add(Application::Ptr& app) { pApps[app->ID()] = app; }
		Desktop& operator += (Application::Ptr& app) { pApps[app->ID()] = app; return *this; }
		Desktop& operator << (Application::Ptr& app) { pApps[app->ID()] = app; return *this; }

		void remove(const String& id) { pApps.erase(id); }
		void remove(Application::Ptr& app) { pApps.erase(app->ID()); }
		Desktop& operator -= (Application::Ptr& app) { pApps.erase(app->ID()); return *this; }

		/*!
		** \brief Close the desktop and all its applications
		*/
		void close();

	private:
		Application::Map pApps;

	}; // class Desktop



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_DESKTOP_H__
