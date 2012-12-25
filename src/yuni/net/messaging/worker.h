#ifndef __YUNI_NET_MESSAGING_WORKER_H__
# define __YUNI_NET_MESSAGING_WORKER_H__

# include "../../yuni.h"
# include "../net.h"
# include "fwd.h"
# include "transport.h"
# include "../../thread/thread.h"
# include "../../thread/array.h"


namespace Yuni
{
namespace Private
{
namespace Net
{
namespace Messaging
{

	/*!
	** \brief Worker for Net queue service
	*/
	class Worker final : public Yuni::Thread::IThread
	{
	public:
		//! The most suitable smart pointer
		typedef Yuni::Thread::IThread::Ptr  Ptr;
		//! Alias to the queue service
		typedef Yuni::Net::Messaging::Service Service;
		//! Transport layer (abstract)
		typedef Yuni::Net::Messaging::Transport::ITransport ITransport;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		explicit Worker(Service& service, ITransport::Ptr transport);
		//! Destructor
		virtual ~Worker();
		//@}

	protected:
		//! Thread execution
		virtual bool onExecute() override;

	protected:
		//! The transport layer
		ITransport::Ptr pTransport;
		//! Pointer to the queue service
		Service& pService;

	}; // class Worker






} // namespace Messaging
} // namespace Net
} // namespace Private
} // namespace Yuni

# include "worker.hxx"

#endif // __YUNI_NET_MESSAGING_WORKER_H__
