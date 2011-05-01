
#include "queueservice.h"


namespace Yuni
{
namespace Net
{
namespace Message
{

	QueueService::QueueService()
		:pMessageMaxSize(messageDefaultMaxSize),
		pState(stStopped)
	{}


	QueueService::~QueueService()
	{
		// Removing all user infos
		pListenInfos.clear();
		// Stopping all workers
		if (pState != stStopped)
			stop();

		// Asserts
		assert(pWorkers.empty() && "All workers must be stopped at this point");
	}



	Error  QueueService::listen(const StringAdapter& address, const Port& port, TransportLayer transport)
	{
		switch (transport)
		{
			case tlTCP:
				return listen(address, port, nullptr);
			case tlUDP:
				return listen(address, port, nullptr);
			default:
				break;
		}
		return errInvalidTransport;
	}



	Error  QueueService::listen(const StringAdapter& address, const Port& port, Transport::ITransport::Ptr transport)
	{
		if (!port.valid())
			return errInvalidPort;
		if (!transport)
			return errInvalidTransport;

		// The address
		ListenInfo::Ptr infos = new ListenInfo();
		infos->address = address;
		if (!infos->address)
			return errInvalidHostAddress;
		infos->port      = port;
		infos->transport = transport;

		// Adding the new address
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pListenInfos.insert(infos).second)
				return errDupplicatedAddress;
		}
		return errNone;
	}


	void QueueService::clear()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pListenInfos.clear();
	}


	unsigned int QueueService::messageMaxSize() const
 	{
 		ThreadingPolicy::MutexLocker locker(*this);
 		return pMessageMaxSize;
 	}
 
 
 	bool QueueService::messageMaxSize(unsigned int size)
 	{
 		if (!size)
 			return false;
 		{
 			ThreadingPolicy::MutexLocker locker(*this);
 			pMessageMaxSize = size;
 		}
 		return true;
 	}


	Error QueueService::sendAll(const char* const buffer, unsigned int length)
	{
		if (!length)
			return errNone;
		if (length < pMessageMaxSize)
		{
			return errNone;
		}
		return errMessageMaxSize;
	}



	Error QueueService::start()
	{
		// Checking if the service is not already running
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (pState != stStopped)
				return (pState == stRunning) ? errNone : errUnknown;
			pState = stStarting;
		}

		Error err = errNone;

		// The internal mutex must be unlocked whenever an event is called to prevent
		// any deadlocks.
		onStarting(err);
		if (err != errNone)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pState = stStopped;
			return err;
		}
		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);
			// Ok, attempt to start the server from the real implementation
			ListenInfo::Set::iterator end = pListenInfos.end();
			for (ListenInfo::Set::iterator i = pListenInfos.begin(); i != end; ++i)
			{
				// The current listen info
				ListenInfo& info = *(*i);
				Worker* worker = new Worker(info.transport);
				pWorkers += worker;
			}
			// The new state
			pState = (err == errNone) ? stRunning : stStopped;
		}
		if (err == errNone)
		{
			// Great ! The server is working !
			onStarted();
			return errNone;
		}
		// An error has occured
		onError(stStarting, err);
		return err;
	}



	Error QueueService::stop()
	{
		// Checking if the service is not already running
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (pState != stRunning)
				return (pState == stStopped) ? errNone : errUnknown;
			pState = stStopping;
		}

		// The internal mutex must be unlocked whenever an event is called to prevent
		// any deadlocks.
		onStopping();

		Error err = errNone;

		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);
			// Ok, stopping all workers
			pWorkers.stop();
			pWorkers.clear();
			// The current state
			pState = (err == errNone) ? stStopped : stRunning;
		}
		if (err == errNone)
		{
			// Great ! The server is working !
			onStopped();
			return errNone;
		}
		// An error has occured
		onError(stStopping, err);
		return err;
	}





} // namespace Message
} // namespace Net
} // namespace Yuni

