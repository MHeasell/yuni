
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
		Workers::Ptr workers;
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
			InitializeInternalData(pData);

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

		// pointer to all workers
		Workers::Ptr workers;

		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);

			// destroy the old instance if not already done
			pData->workers = nullptr;

			// destroy all workers, just to be sure
			workers = new Workers();
			// disable the autostart
			workers->autoStart(false);

			// Ok, attempt to start the server from the real implementation
			// recreating all workers
			TransportList& transports = pData->transports;

			if (not transports.empty())
			{
				TransportList::iterator end = transports.end();
				for (TransportList::iterator i = transports.begin(); i != end; ++i)
				{
					// start the transport
					if (errNone != (err = (*i)->start()))
						break;

					// creating a new worker
					*workers += new Yuni::Private::Net::Messaging::Worker(*this, *i);
				}

				// The new state
				if (err == errNone)
				{
					pData->workers = workers;
					pState = stRunning;
				}
				else
					pState = stStopped;
			}
			else
			{
				err = errNoTransport;
				pState = stStopped;
			}
		}

		if (err == errNone)
		{
			// start all workers
			workers->start();

			// Great ! The server is working !
			events.started();
			return errNone;
		}

		if (!(!workers))
		{
			workers->stop();
			workers = nullptr; // should be destroyed here
		}

		// An error has occured
		events.error(stStarting, err);
		return err;
	}


	void Service::wait()
	{
		Workers::Ptr workers;

		// retrieving a pointer to the workers
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (pData)
				workers = pData->workers;
			else
				return;
		}

		if (!(!workers))
			workers->wait();
	}


	Error Service::stop()
	{
		// Checking if the service is not already running
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (pData == NULL or not pData->workers)
				return errNone;
			if (pState != stRunning)
				return (pState == stStopped) ? errNone : errUnknown;
			pState = stStopping;
		}

		// The internal mutex must be unlocked whenever an event is called to prevent
		// any deadlocks.
		events.stopping();

		Error err = errNone;
		Workers::Ptr workers;

		// Trying to start all workers
		{
			ThreadingPolicy::MutexLocker locker(*this);

			workers = pData->workers;
			pData->workers = nullptr;
			// The current state
			pState = (err == errNone) ? stStopped : stRunning;
		}

		if (err == errNone)
		{
			// stopping then destroying all workers
			if (!(!workers))
			{
				workers->stop();
				workers = nullptr; // should be destroyed here
			}
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
