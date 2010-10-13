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
		typedef CustomString<40, false, false> GUID;

		//! Map from a unique ID
		typedef std::map<GUID, Application::Ptr> Map;


	public:
		/*!
		** \brief Constructor
		*/
		template<typename StringT, typename StringT2>
		Application(const StringT& id, const StringT2& name);

		/*!
		** \brief Get the identifier for this application
		*/
		const GUID& guid() const;

		/*!
		** \brief Get the name of this application
		*/
		const String& name() const;


		//! \name Add or remove windows
		//@{
		void add(const Window::Ptr& wnd);

		void remove(IComponent::ID id);

		void remove(const Window::Ptr& wnd);

		Application& operator += (Window* wnd);
		Application& operator += (const Window::Ptr& wnd);
		Application& operator << (Window* wnd);
		Application& operator << (const Window::Ptr& wnd);

		Application& operator -= (IComponent::ID id);
		Application& operator -= (Window* wnd);
		Application& operator -= (const Window::Ptr& wnd);
		//@}

	private:
		//! Application string identifier
		GUID pGUID;

		//! Application name, used for display
		String pName;

		//! Application windows
		Window::Map pWindows;


	}; // class Application



} // namespace UI
} // namespace Yuni


# include "application.hxx"


#endif // __YUNI_UI_APPLICATION_H__
