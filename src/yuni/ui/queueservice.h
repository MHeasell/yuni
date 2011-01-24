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
		typedef std::pair<Window*, Private::UI::Local::IWindow*>  WindowPair;
		typedef std::map<IComponent::ID, WindowPair>  WindowMap;
		typedef std::map<GUID, WindowMap>  ApplicationWindowMap;
		//! Component storage with unique identifiers to access them
		typedef std::map<GUID, std::map<IComponent::ID, IComponent*> >  Components;


	public:
		//! \name Delegate parameter types
		//@{
		struct ShowWindowParams
		{
			typedef SmartPtr<ShowWindowParams> Ptr;

			GUID applicationGUID;

			Window::Ptr window;

			ShowWindowParams(GUID appID, const Window::Ptr& windowPtr)
				: applicationGUID(appID), window(windowPtr)
			{}
		};

		struct ModifyWindowParams
		{
			typedef SmartPtr<ModifyWindowParams> Ptr;

			GUID applicationGUID;

			IComponent::ID windowID;

			ModifyWindowParams(GUID appID, const IComponent::ID& window)
				: applicationGUID(appID), windowID(window)
			{}
		};

		struct ResizeWindowParams
		{
			typedef SmartPtr<ResizeWindowParams> Ptr;

			GUID applicationGUID;

			IComponent::ID windowID;

			float width;

			float height;

			ResizeWindowParams(GUID appID, const IComponent::ID& window, float w, float h)
				: applicationGUID(appID), windowID(window), width(w), height(h)
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
		void showWindow(const GUID& appID, Window* window);
		void hideWindow(const GUID& appID, const IComponent::ID& windowID);
		void closeWindow(const GUID& appID, const IComponent::ID& windowID);
		void resizeWindow(const GUID& appID, const IComponent::ID& windowID, float width, float height);

		void showComponent(const GUID& appID, IComponent::Ptr component);
		void hideComponent(const GUID& appID, const IComponent::ID& componentID);
		void updateComponent(const GUID& appID, const IComponent::ID& componentID);


	protected:
		//! UI tree root
		Desktop::Ptr pDesktop;
		//! Store visible windows
		ApplicationWindowMap pVisibleWindows;
		//! Store visible components
		Components pVisibleComponents;

		//! Friend: required for access to events
		friend class Desktop;

	}; // class QueueService





} // namespace UI
} // namespace Yuni

# include "queueservice.hxx"

#endif // __YUNI_UI_QUEUESERVICE_H__
