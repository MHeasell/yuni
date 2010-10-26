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

	//! Forward declaration
	class Desktop;


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
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default application
		*/
		Application();
		/*!
		** \brief Constructor with a given name
		*/
		template<class StringT> explicit Application(const StringT& name);
		/*!
		** \brief Destructor
		*/
		~Application();
		//@}


		//! Quit the application
		void quit();

		/*!
		** \brief Get the identifier for this application
		*/
		const GUID& guid() const;

		/*!
		** \brief Get the name of this application
		*/
		const String& name() const;

		//! Generate a locally unique ID
		IComponent::ID createID() const;


		//! \name Windows
		//@{
		void add(const Window::Ptr& wnd);

		void remove(IComponent::ID id);

		void remove(const Window::Ptr& wnd);
		//@}


		//! \name Operators
		//@{
		Application& operator += (Window* wnd);
		Application& operator += (const Window::Ptr& wnd);
		Application& operator << (Window* wnd);
		Application& operator << (const Window::Ptr& wnd);

		Application& operator -= (IComponent::ID id);
		Application& operator -= (Window* wnd);
		Application& operator -= (const Window::Ptr& wnd);
		//@}


	protected:
		//! Application string identifier
		const GUID pGUID;
		//! Application name, used for display
		String pName;
		//! Application windows
		Window::Map pWindows;
		//! Parent desktop
		Desktop* pDesktop;

	private:
		/*!
		** \brief Generate a GUID (Globally unique identifier) for an application
		*/
		static void GenerateGUID(GUID& guid);

		//! Initialize all internal stuff
		void initialize();

		/*!
		** \brief Update the given component's local representation
		*/
		void updateComponentWL(const IComponent::ID& componentID) const;


	}; // class Application




} // namespace UI
} // namespace Yuni

# include "desktop.h"
# include "application.hxx"

#endif // __YUNI_UI_APPLICATION_H__
