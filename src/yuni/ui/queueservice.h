#ifndef __YUNI_UI_QUEUESERVICE_H__
# define __YUNI_UI_QUEUESERVICE_H__

# include "../yuni.h"
# include "../core/event/event.h"
# include "../core/event/loop.h"
# include "desktop.h"
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
		: public Core::EventLoop::IEventLoop<IQueueService<ChildT>,
		Core::EventLoop::Flow::Continuous, Core::EventLoop::Statistics::None, false>,
		public IEventObserver<IQueueService<ChildT> >
	{
	public:
		//! Event loop type
		typedef typename Core::EventLoop::template IEventLoop<IQueueService<ChildT>,
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
		typedef IEventObserver<IQueueService<ChildT> >  EventObserverType;

		//! Window association map
		typedef std::map<Application::GUID, std::map<IComponent::ID, Window*> >  WindowMap;
		//! Component storage with unique identifiers to access them
		typedef std::map<Application::GUID, std::map<IComponent::ID, IComponent*> >  Components;


	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		IQueueService();
		//! Destructor
		~IQueueService();
		//@}

	public:
		//! UI tree root
		Desktop::Ptr desktop;

	protected:
		//! Store windows that have been modified
		WindowMap pModifiedWindows;
		//! Store components that have been modified
		Components pModifiedComponents;

	}; // class QueueService





} // namespace UI
} // namespace Yuni

# include "queueservice.hxx"

#endif // __YUNI_UI_QUEUESERVICE_H__
