#ifndef __YUNI_NET_MESSAGING_SERVICE_H__
# define __YUNI_NET_MESSAGING_SERVICE_H__

# include "../../yuni.h"
# include "../net.h"
# include "../../thread/policy.h"
# include "../../core/event.h"
# include "fwd.h"
# include "transport.h"
# include "../../core/noncopyable.h"
# include "protocol.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{


	class YUNI_DECL Service final : private Yuni::NonCopyable<Service>, public Policy::ObjectLevelLockable<Service>
	{
	public:
		//! The threading policy
		typedef Policy::ObjectLevelLockable<Service>  ThreadingPolicy;

		/*!
		** \brief Different states of a queue service
		*/
		enum State
		{
			//! The queue service is currently stopped
			stStopped,
			//! The queue service is currently starting
			stStarting,
			//! The queue service is working
			stRunning,
			//! The queue service is current stopping its work
			stStopping
		};


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Service();
		//! Destructor
		~Service();
		//@}


		//! \name Service management
		//@{
		/*!
		** \brief Try to start the queue service
		*/
		Error start();

		/*!
		** \brief Wait for the service to stop
		*/
		void wait();

		/*!
		** \brief Stop the server
		*/
		Error stop();

		//! Get if the queueservice is running (state running / starting)
		bool running() const;
		//@}


		//! \name Protocol
		//@{
		/*!
		** \brief Install a new protocol
		**
		** \note This method will take ownership of the pointer, thus this pointer
		**   should not be used any longer
		**
		** \param newapi The new protocol (can be null)
		*/
		void protocol(Protocol* newapi);
		//@}


	public:
		//! Listeners management
		class Transports final : private NonCopyable<Transports>
		{
		public:
			/*!
			** \brief Add a new transport for a list of addresses and a specific port
			**
			** This action will be effective the next time the server starts
			** \code
			** Net::Messaging::Service  server;
			** server.addListener("82.125.10.31", 4242, new Net::Transport::REST());
			** server.start();
			** server.wait();
			** server.stop();
			** \endcode
			*/
			Error add(const AnyString& address, const Port& port, Transport::ITransport::Ptr transport);

			/*!
			** \brief Add a new transport for *:<port>
			*/
			Error add(const Port& port, Transport::ITransport::Ptr transport);

			/*!
			** \brief Clear all addresses where the server should listen for incoming connections
			**
			** This action will be effective the next time the server starts
			*/
			void clear();


		private:
			Service* pService;
			friend class Service;
		}
		transports;


		//! Events
		class Events final : private NonCopyable<Events>
		{
		public:
			//! Prototype event: The queue service is starting
			typedef Event<void (Error&)> Starting;
			//! Prototype event: The queue service has started
			typedef Event<void ()> Started;
			//! Prototype event: The queue service is stopping
			typedef Event<void ()> Stopping;
			//! Prototype event: The queue service has been stopped
			typedef Event<void ()> Stopped;
			//! Prototype event: An error has occured
			typedef Event<void (State, Error)> ErrorTriggered;
			//! Prototype event: accepting a client
			typedef Event<void (bool&, const String&, Port, const String&, Port)> ClientAccept;

		public:
			//! Event: The queue service is starting
			Starting starting;
			//! Event: The queue service has started and is ready for incoming connections
			Started  started;
			//! Event: The queue service is shutting down
			Stopping stopping;
			//! Event: The queue service is stopped
			Stopped  stopped;
			//! Event: The queue service has encountered an error
			ErrorTriggered  error;
			//! Event: A client try to connect to the server
			ClientAccept   accept;
			//! Event: A client has been successfully connected to the server
		}
		events;


	protected:
		//! Flag to know the state of the server
		State pState;
		//! Internal data
		Yuni::Private::Net::Messaging::ServiceData* pData;

		// Friends
		friend class Yuni::Private::Net::Messaging::Worker;
		friend class Listeners;

	}; // class Service






} // namespace Messaging
} // namespace Net
} // namespace Yuni

# include "service.hxx"

#endif // __YUNI_NET_MESSAGING_SERVICE_H__
