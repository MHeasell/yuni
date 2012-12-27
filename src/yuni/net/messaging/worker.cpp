
#include "worker.h"
#include "service.h"


namespace Yuni
{
namespace Private
{
namespace Net
{
namespace Messaging
{

	Worker::Worker(Service& service, ITransport::Ptr transport) :
		pTransport(transport),
		pService(service)
	{
	}


	Worker::~Worker()
	{
		stop();
	}


	bool Worker::onExecute()
	{
		// note : this method should not keep a lock on the smart pointer.
		// A memory leak would happen if the thread is killed in action.
		if (!(!pTransport)) // valid pointer to transport
		{
			// pointer aliasing
			ITransport& transport = *pTransport;

			// Attach the current thread to the transport layer
			transport.attachedThread(this);

			// run the transport layer, and wait for it
			Yuni::Net::Error error = transport.run();

			if (error != Yuni::Net::errNone)
				pService.events.error(Service::stRunning, error);
		}
		return false;
	}


	void Worker::onStop()
	{
		// getting apointer to the transport
		ITransport::Ptr transport = pTransport;
		if (!(!transport))
		{
			// Detach the thread, just in case
			transport->attachedThread(nullptr);
			// directly unassign / destroy the transport here (from the thread
			// to avoid long unexplained delay from the destructor
			pTransport = nullptr;
		}
	}


	void Worker::onKill()
	{
		onStop();
	}





} // namespace Messaging
} // namespace Net
} // namespace Private
} // namespace Yuni

