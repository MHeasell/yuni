#ifndef __YUNI_NET_SERVER_SERVER_H__
# define __YUNI_NET_SERVER_SERVER_H__

# include "../../yuni.h"
# include "../net.h"
# include "../../thread/policy.h"


namespace Yuni
{
namespace Net
{
namespace Server
{

	enum
	{
		//! The default value for the maximum size of a message
		defaultMessageMaxSize = 10 * 1024 * 1024,
	};




	template<class ImplT, class UserDataT = Empty>
	class IServerTmpl :
		public    Policy::ObjectLevelLockable<IServerTmpl<ImplT> >,
		protected ImplT
	{
	public:
		//! The server implementation
		typedef ImplT  ImplementationType;
		//! Server
		typedef IServerTmpl<ImplT>  ServerTmplType;
		//! The threading policy
		typedef Policy::ObjectLevelLockable<IServerTmpl<ImplT> >  ThreadingPolicy;

		//! Connection
		typedef ConnectionTmpl<ImplT::ConnectionData, UserDataT>  Connection;

		//! Prototype event: The server is starting
		typedef Event<void (Error&)> OnStarting;
		//! Prototype event: The server has started
		typedef Event<void ()> OnStarted;
		//! Prototype event: The server is stopping
		typedef Event<void ()> OnStopping;
		//! Prototype event: The server has been stopped
		typedef Event<void ()> OnStopped;
		//! Prototype event: accepting a client
		typedef Event<void (bool&, const String&, Port, const String&, Port)> OnClientAccept;
		//! Prototype event: A client has connected
		typedef Event<void (const Connection::Ptr&)> OnClientConnected;
		//! Prototype event: A client has disconnected
		typedef Event<void (const Connection::Ptr&)> OnClientDisconnected;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		IServerTmpl();
		//! Destructor
		~IServerTmpl();
		//@}


		//! \name Addresses management
		//@{
		/*!
		** \brief Add a new address where the server should listen for incoming connections
		**
		** This action will be effective the next time the server starts
		** \code
		** Net::Server::TCP  server;
		** server.listen("::1", 4242);
		** server.listen("82.125.10.31", 4242);
		** server.start();
		** \endcode
		*/
		template<class StringT> Error  listen(const StringT& address, const Port& port);

		/*!
		** \brief Clear all addresses where the server should listen for incoming connections
		**
		** This action will be effective the next time the server starts
		*/
		void clear();
		//@}


		//! \name Service
		//@{
		/*!
		** \brief Start the server
		*/
		Error start();

		/*!
		** \brief Stop the server
		*/
		Error stop(unsigned int timeout = 5000);

		/*!
		** \brief Restart the server
		*/
		Error  restart();
		//@}


		//! \name Messages
		//@{
		/*!
		** \brief Send a buffer to all clients
		**
		** Nothing will be done if the size is null (but return errNone), or
		** greater than messageMaxSize(returns errMessageMaxSize).
		**
		** \param buffer A raw buffer
		** \param size Size in bytes of the buffer
		** \return errNone if the operation succeeded
		*/
		Error  sendAll(const char* const buffer, unsigned int size);

		/*!
		** \brief Send a buffer to all clients
		**
		** Nothing will be done if the size is null (but return errNone), or
		** greater than messageMaxSize(returns errMessageMaxSize).
		**
		** \param buffer A buffer
		** \return errNone if the operation succeeded
		*/
		template<class StringT> Error  sendAll(const StringT& buffer);


		//! Get the maximum size (in bytes) of a message
		unsigned int messageMaxSize() const;
		//! Set the maximum size (in bytes, > 0) of a message
		bool messageMaxSize(unsigned int size);
		//@}

	public:
		//! \name Events
		//@{
		//! Event: The server is starting
		OnStarting onStarting;
		//! Event: The server has started and is ready for incoming connections
		OnStarter  onStarted;
		//! Event: The server is shutting down
		OnStopping onStopping;
		//! Event: The server is stopped
		OnStopped  onStopped;
		//! Event: A client try to connect to the server
		OnClientAccept   onClientAccept();
		//! Event: A client has been successfully connected to the server
		OnClientConnected   onClientConnected;
		//! Event: A client has been disconnected from the server
		OnClientDisconnected  onClientDisconnected;
		//@}


	private:
		//! All addresses to listen
		HostAddressPort::Set  pAddresses;
		//! The maximum size (in bytes) of a message
		unsigned int pMessageMaxSize;
		//! Flag to know if the server is currently working
		bool pRunning;

	}; // class IServerTmpl





} // namespace Server
} // namespace Net
} // namespace Yuni

# include "server.hxx"

#endif // __YUNI_NET_SERVER_SERVER_H__
