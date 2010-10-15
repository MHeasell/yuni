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
		void add(Application::Ptr& app);
		Desktop& operator += (Application::Ptr& app);
		Desktop& operator << (Application::Ptr& app);

		template<typename StringT>
		void remove(const StringT& id);
		void remove(Application::Ptr& app);
		template<typename StringT>
		Desktop& operator -= (const StringT& id);
		Desktop& operator -= (Application::Ptr& app);

		/*!
		** \brief Quit the desktop and all its applications
		*/
		void quit();

	private:
		Application::Map pApps;

	}; // class Desktop



} // namespace UI
} // namespace Yuni

# include "desktop.hxx"

#endif // __YUNI_UI_DESKTOP_H__
