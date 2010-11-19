#ifndef __YUNI_UI_APPLICATION_H__
# define __YUNI_UI_APPLICATION_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "../core/event.h"
# include "fwd.h"
# include "window.h"

namespace Yuni
{
namespace UI
{

	/*!
	** \brief Virtual application. Can contain one or several windows.
	*/
	class Application: public IEventObserver<Application>
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Application> Ptr;

		//! String identifier type
		typedef CustomString<40, false, false> GUID;

		//! Map from a unique ID
		typedef std::map<GUID, Application::Ptr> Map;

		//! Event observer type
		typedef IEventObserver<Application> EventObserverType;

		//! Threading policy
		typedef EventObserverType::ThreadingPolicy ThreadingPolicy;


	public:
		static const GUID InvalidGUID;

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

		//! Show all the application's windows
		void show();

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
		//! Add a window to the application
		void add(const Window::Ptr& wnd);

		//! Remove a window from the application using its ID
		void remove(IComponent::ID id);

		//! Remove a window from the application
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
		//! \name Events
		//@{
		Event<void (const Application::GUID&, Window::Ptr)>* onApplicationShowWindow;
		Event<void (const Application::GUID&, const IComponent::ID&)>* onApplicationHideWindow;
		Event<void (const Application::GUID&, const IComponent::ID&)>* onApplicationCloseWindow;
		Event<void (const Application::GUID&, IComponent::Ptr)>* onApplicationShowComponent;
		Event<void (const Application::GUID&, const IComponent::ID&)>* onApplicationHideComponent;
		Event<void (const Application::GUID&, const IComponent::ID&)>* onApplicationUpdateComponent;
		//@}

		void showWindow(Window::Ptr window);
		void hideWindow(const IComponent::ID& windowID);
		void closeWindow(const IComponent::ID& windowID);

		void showComponent(IComponent::Ptr component);
		void hideComponent(const IComponent::ID& componentID);
		void updateComponent(const IComponent::ID& componentID);

		//! Connect children windows to events
		void reconnect();
		void reconnectWL();
		void reconnectOneWindowWL(Window::Ptr window);

		//! Disconnect events
		void disconnect();
		void disconnectWL();


	protected:
		//! Application string identifier
		const GUID pGUID;
		//! Application name, used for display
		String pName;
		//! Application windows
		Window::Map pWindows;


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


		//! Friend : required for access to events
		friend class Desktop;

	}; // class Application




} // namespace UI
} // namespace Yuni

# include "desktop.h"
# include "application.hxx"

#endif // __YUNI_UI_APPLICATION_H__
