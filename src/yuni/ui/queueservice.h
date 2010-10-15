#ifndef __YUNI_UI_QUEUESERVICE_H__
# define __YUNI_UI_QUEUESERVICE_H__

# include "application.h"
# include "../gfx/device.h"
# include "../core/event/event.h"
# include "../core/event/loop.h"
# include "desktop.h"



namespace Yuni
{
namespace UI
{

	/*!
	** \brief UI queue service
	*/
	class IQueueService
		: public Core::EventLoop::IEventLoop<IQueueService, Core::EventLoop::Flow::Continuous,
		Core::EventLoop::Statistics::None, false>
		, public IEventObserver<IQueueService>
	{
	public:
		//! Event loop type
		typedef Core::EventLoop::IEventLoop<IQueueService,
			Core::EventLoop::Flow::Continuous, // The flow policy
			Core::EventLoop::Statistics::None, // The statistics policy
			false>                             // Run in the main thread
			Type;

		//! Threading policy
		typedef Type::ThreadingPolicy  ThreadingPolicy;
		//! Smart pointer
		typedef SmartPtr<IQueueService> Ptr;


	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		IQueueService();
		//! Destructor
		virtual ~IQueueService();
		//@}


	public:
		//! UI tree root
		Desktop::Ptr desktop;


	public:
		//! Run on each loop turn.
		virtual bool onLoop() = 0;

	}; // class QueueService





} // namespace UI
} // namespace Yuni

# include "queueservice.hxx"

#endif // __YUNI_UI_QUEUESERVICE_H__
