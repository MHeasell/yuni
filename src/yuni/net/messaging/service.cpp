
#include "service.h"
#include "worker.h"
#include "../../thread/array.h"


typedef Yuni::Thread::Array<Yuni::Private::Net::Messaging::Worker>  Workers;

typedef Yuni::Net::Messaging::Transport::ITransport::Set  TransportList;



namespace Yuni
{
namespace Private
{
namespace Net
{
namespace Messaging
{

	class ServiceData
	{
	public:
		//! All workers
		Workers workers;
		//! All addresses to listen
		TransportList transports;
		//! Protocol
		Yuni::Net::Messaging::Protocol::Ptr protocol;

	}; // class ServiceData



} // namespace Messaging
} // namespace Net
} // namespace Private
} // namespace Yuni




namespace Yuni
{
namespace Net
{
namespace Messaging
{

	//! ensuring that the internal data is properly initialized
	static inline void InitializeInternalData(Yuni::Private::Net::Messaging::ServiceData*& data)
	{
		if (not data)
			data = new Yuni::Private::Net::Messaging::ServiceData();
	}



	Service::Service() :
		pState(stStopped),
		pData(nullptr)
	{
		transports.pService = this;
	}


	Service::~Service()
	{
		// Stopping all workers
		stop();

		// for code robustness
		ThreadingPolicy::MutexLocker locker(*this);
		// release internal data
		delete pData;
	}


	Error  Service::Transports::add(const AnyString& address, const Port& port, Transport::ITransport::Ptr transport)
	{
		if (not port.valid())
			return errInvalidPort;
		if (not transport or transport->mode != Transport::tmServer)
			return errInvalidTransport;

		// The address
		if (not address)
			return errInvalidHostAddress;
		transport->address = address;
		transport->port    = port;

		// Adding the new address
		{
			ThreadingPolicy::MutexLocker locker(*pService);
			InitializeInternalData(pService->pData);
			if (not pService->pData->transports.insert(transport).second)
				return errDupplicatedAddress;
		}
		return errNone;
	}


	void Service::Transports::clear()
	{
		ThreadingPolicy::MutexLocker locker(*pService);
		if (pService->pData)
			pService->pData->transports.clear();
	}


	Error Service::start()
	{
		// Checking if the service is not already running
		{
			ThreadingPolicy::MutexLocker locker(*this);

			// Directly stop if there is no transport available
			if (not pData or pData->transports.empty())
			{
				pState = stStopped;
				return errNoTransport;
			}

			// checking the current state
			if (pState != stStopped)
				return (pState == stRunning) ? errNone : errUnknown;

			// ok, let's start
			pState = stStarting;
		}

		// note: from now on, we know that pData is initialized due to the previous check

		// no error by default
		Error err = errNone;

		// The internal mutex must be unlocked whenever an event is called to prevent
		// any deadlocks.
		events.starting(err);
		if (err != errNone)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pState = stStopped;
			return err;
		}

		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);

			// destroy all workers, just to be sure
			Workers& workers = pData->workers;
			workers.stop();
			workers.clear();
			// Ok, attempt to start the server from the real implementation
			// recreating all workers
			TransportList& transports = pData->transports;
			TransportList::iterator end = transports.end();
			for (TransportList::iterator i = transports.begin(); i != end; ++i)
			{
				// start the transport
				if (errNone != (err = (*i)->start()))
					break;

				// creating a new worker
				workers += new Yuni::Private::Net::Messaging::Worker(*this, *i);
			}

			// The new state
			pState = (err == errNone) ? stRunning : stStopped;
		}

		if (err == errNone)
		{
			// Great ! The server is working !
			events.started();
			return errNone;
		}
		else
		{
			ThreadingPolicy::MutexLocker locker(*this);
			// destroy all workers
			Workers& workers = pData->workers;
			workers.stop();
			workers.clear();
		}

		// An error has occured
		events.error(stStarting, err);
		return err;
	}


	void Service::wait()
	{
	}


	Error Service::stop()
	{
		// Checking if the service is not already running
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (pData == NULL)
				return errNone;
			if (pState != stRunning)
				return (pState == stStopped) ? errNone : errUnknown;
			pState = stStopping;
		}

		// The internal mutex must be unlocked whenever an event is called to prevent
		// any deadlocks.
		events.stopping();

		Error err = errNone;

		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);

			// destroy all workers
			Workers& workers = pData->workers;
			workers.stop();
			workers.clear();
			// The current state
			pState = (err == errNone) ? stStopped : stRunning;
		}

		if (err == errNone)
		{
			// Great ! The server is working !
			events.stopped();
			return errNone;
		}

		// An error has occured
		events.error(stStopping, err);
		return err;
	}


	bool Service::running() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return (pState == stStarting) or (pState == stRunning);
	}


	void Service::protocol(Protocol* newapi)
	{
		// creating a new smart pointer for the new api
		Protocol::Ptr newproto = (not newapi) ? new Protocol() : newapi;

		// Locking the whole object
		ThreadingPolicy::MutexLocker locker(*this);

		// making sure that internal data are allocated
		InitializeInternalData(pData);
		assert(pData != NULL && "internal error");

		// Making all transports switch to the new protocol


		// All transports have switched to the new protocol
		// we can release our own pointer. The old protocol should
		// be destroyed here, in the current thread, instead
		// of inside a worker of one of the transports
		pData->protocol = newproto;
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

