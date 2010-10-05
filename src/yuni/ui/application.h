#ifndef __YUNI_UI_APPLICATION_H__
# define __YUNI_UI_APPLICATION_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "window.h"

namespace Yuni
{
namespace UI
{


	/*!
	** \brief Virtual application. Can contain one or several windows.
	*/
	class Application
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Application> Ptr;

		//! String identifier type
		typedef CustomString<40, false, false> StaticString;

		//! Map from a unique ID
		typedef std::map<StaticString, Application::Ptr> Map;


	public:
		/*!
		** \brief Constructor
		*/
		template<typename StringT, typename StringT2>
		Application(const StringT& id, const StringT2& name);

		/*!
		** \brief Close the application
		*/
		void close();

		/*!
		** \brief Get the identifier for this application
		*/
		const StaticString& id();

		/*!
		** \brief Get the name of this application
		*/
		const StaticString& name();


		//! \name Add or remove windows
		//@{
		void add(Window::Ptr& wnd);
		Application& operator += (Window::Ptr& wnd);
		Application& operator << (Window::Ptr& wnd);

		void remove(IComponent::ID id);
		void remove(Window::Ptr& app);
		Application& operator -= (IComponent::ID id);
		Application& operator -= (Window::Ptr& app);

		//@}

	private:
		//! Application string identifier
		StaticString pID;

		//! Application name, used for display
		StaticString pName;

		//! Application windows
		Window::Map pWindows;


	}; // class Application



} // namespace UI
} // namespace Yuni


# include "application.hxx"


#endif // __YUNI_UI_APPLICATION_H__
