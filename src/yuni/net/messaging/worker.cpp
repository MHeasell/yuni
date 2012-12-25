
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
	{}


	Worker::~Worker()
	{
		stop();
	}


	bool Worker::onExecute()
	{
		if (!(!pTransport)) // valid pointer to transport
		{
			// The current transport layer
			ITransport& transport = *pTransport;

			// Attach the current thread to the transport layer
			transport.attachedThread(this);

			// run the transport layer, and wait for it
			Yuni::Net::Error error = transport.run();

			// Detach the thread, just in case
			transport.attachedThread(nullptr);

			if (error != Yuni::Net::errNone)
				pService.events.error(Service::stRunning, error);

			// directly unassign / destroy the transport here (from the thread
			// to avoid long unexplained delay
			pTransport = nullptr;
		}
		return true;
	}





} // namespace Messaging
} // namespace Net
} // namespace Private
} // namespace Yuni

