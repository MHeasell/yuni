#ifndef __YUNI_UI_DESKTOP_H__
# define __YUNI_UI_DESKTOP_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../core/event/event.h"
# include "fwd.h"
# include "application.h"


namespace Yuni
{
namespace UI
{


	/*!
	** \brief Virtual desktop meant to receive one or several applications
	*/
	class YUNI_EXPORT Desktop: public IEventObserver<Desktop>
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Desktop> Ptr;
		//! Threading policy
		typedef IEventObserver<Desktop> EventObserverType;
		//! Threading policy
		typedef EventObserverType::ThreadingPolicy ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Desktop();
		//! Destructor
		~Desktop();
		//@}


		//! \name Applications
		//@{
		/*!
		** \brief Add an application to this desktop
		*/
		void add(const Application::Ptr& app);

		/*!
		** \brief
		*/
		template<typename StringT> void remove(const StringT& id);
		//!
		void remove(const Application::Ptr& app);
		//@}

		/*!
		** \brief Show all applications and windows in this desktop
		*/
		void show();

		/*!
		** \brief Quit the desktop and all its applications
		*/
		void quit();


		void reconnectLocalEvents(LocalUIEvents& events);


		//! \name Operators
		//@{
		//! Register a new application
		//! \see add()
		Desktop& operator += (const Application::Ptr& app);
		//! Register a new application
		//! \see add()
		Desktop& operator << (const Application::Ptr& app);

		//! Remove an application from its guid
		//! \see remove()
		template<typename StringT> Desktop& operator -= (const StringT& id);
		//! Remove an application from its pointer
		//! \see remove()
		Desktop& operator -= (const Application::Ptr& app);
		//@}


	public:
		//!
		Event<void ()> onDisconnectLocalEvents;

	private:
		//! Reconnect events on contained applications
		void reconnect();
		void reconnectWL();
		void reconnectOneApplicationWL(const Application::Ptr& app);

		//! Disconnect all events, and propagate to applications
		void disconnect();
		void disconnectWL();


	private:
		//! Applications stored in this desktop
		Application::Map pApps;

		LocalUIEvents pLocalEvents;

		//! Friend: required for access to events
		template<class> friend class IQueueService;

	}; // class Desktop



} // namespace UI
} // namespace Yuni

# include "queueservice.h"
# include "desktop.hxx"

#endif // __YUNI_UI_DESKTOP_H__
