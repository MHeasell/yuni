#ifndef __YUNI_UI_QUEUESERVICE_H__
# define __YUNI_UI_QUEUESERVICE_H__

# include "../yuni.h"
# include "../core/event/event.h"
# include "../core/event/loop.h"
# include "desktop.h"
# include "fwd.h"
# include <map>


namespace Yuni
{
namespace UI
{

	/*!
	** \brief UI queue service
	*/
	template<class ChildT>
	class IQueueService
		: public Core::EventLoop::IEventLoop<ChildT,
		Core::EventLoop::Flow::Continuous, Core::EventLoop::Statistics::None, false>,
		public IEventObserver<IQueueService<ChildT> >
	{
	public:
		//! Event loop type
		typedef typename Core::EventLoop::template IEventLoop<ChildT,
			Core::EventLoop::Flow::Continuous, // The flow policy
			Core::EventLoop::Statistics::None, // The statistics policy
			false>                             // Run in the main thread
			Type;

		//! Threading policy
		typedef typename Type::ThreadingPolicy  ThreadingPolicy;
		//! Smart pointer
		typedef SmartPtr<IQueueService<ChildT> > Ptr;
		//! Child type
		typedef ChildT ChildType;
		typedef IQueueService<ChildT> RealType;
		typedef IEventObserver<IQueueService<ChildT> >  EventObserverType;
		typedef Core::EventLoop::IEventLoop<ChildT,
			Core::EventLoop::Flow::Continuous, Core::EventLoop::Statistics::None, false>  EventLoopType;

		//! Request types
		typedef typename EventLoopType::RequestType  RequestType;

		//! Window association map
		typedef std::map<IComponent::ID, std::pair<Window*, Private::UI::Local::IWindow*> > WindowMap;
		typedef std::map<Application::GUID, WindowMap>  ApplicationWindowMap;
		//! Component storage with unique identifiers to access them
		typedef std::map<Application::GUID, std::map<IComponent::ID, IComponent*> >  Components;


	public:
		//! \name Delegate parameter types
		//@{
		struct ShowWindowParams
		{
			typedef SmartPtr<ShowWindowParams> Ptr;

			Application::GUID applicationGUID;

			Window::Ptr window;

			ShowWindowParams(Application::GUID appID, const Window::Ptr& windowPtr)
				: applicationGUID(appID), window(windowPtr)
			{}
		};
		//@}

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		IQueueService();
		//! Destructor
		~IQueueService();
		//@}

	public:
		//! Set / Get UI tree root
		Desktop::Ptr desktop() const;
		void desktop(Desktop::Ptr newDesktop);

	protected:
		//! "Show window" event
		Event<void (const Application::GUID& appID, Window::Ptr)> onShowWindow;
		//! "Hide window" event
		Event<void (const Application::GUID& appID, const IComponent::ID&)> onHideWindow;
		//! "Close window" event
		Event<void (const Application::GUID& appID, const IComponent::ID&)> onCloseWindow;

		//! "Show component" event
		Event<void (const Application::GUID& appID, IComponent::Ptr)> onShowComponent;
		//! "Hide component" event
		Event<void (const Application::GUID& appID, const IComponent::ID&)> onHideComponent;
		//! "Update component" event
		Event<void (const Application::GUID& appID, const IComponent::ID&)> onUpdateComponent;

	protected:
		void showWindow(const Application::GUID& appID, Window::Ptr window);
		void hideWindow(const Application::GUID& appID, const IComponent::ID& windowID);
		void closeWindow(const Application::GUID& appID, const IComponent::ID& windowID);

		void showComponent(const Application::GUID& appID, IComponent::Ptr component);
		void hideComponent(const Application::GUID& appID, const IComponent::ID& componentID);
		void updateComponent(const Application::GUID& appID, const IComponent::ID& componentID);


	protected:
		//! UI tree root
		Desktop::Ptr pDesktop;
		//! Store windows that have been modified
		ApplicationWindowMap pVisibleWindows;
		//! Store components that have been modified
		Components pVisibleComponents;

		//! Friend: required for access to events
		friend class Desktop;

	}; // class QueueService





} // namespace UI
} // namespace Yuni

# include "queueservice.hxx"

#endif // __YUNI_UI_QUEUESERVICE_H__
