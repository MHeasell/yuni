#ifndef __YUNI_NET_MESSAGE_WORKER_H__
# define __YUNI_NET_MESSAGE_WORKER_H__

# include "../../yuni.h"
# include "../net.h"
# include "transport.h"
# include "../../thread/thread.h"
# include "../../thread/array.h"


namespace Yuni
{
namespace Private
{
namespace Net
{
namespace Message
{


	class Worker : public Yuni::Thread::IThread
	{
	public:
		//! Transport layer (abstract)
		typedef Yuni::Net::Message::Transport::ITransport ITransport;
		//! The most suitable smart pointer
		typedef Yuni::Thread::IThread::Ptr  Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		explicit Worker(ITransport::Ptr transport);
		//! Destructor
		~Worker();
		//@}

	protected:
		//! Thread execution
		virtual bool onExecute();

	private:
		//! The transport layer
		Yuni::Net::Message::Transport::ITransport::Ptr pTransport;

	}; // class Worker




} // namespace Message
} // namespace Net
} // namespace Private
} // namespace Yuni

#endif // __YUNI_NET_MESSAGE_QUEUESERVICE_WORKER_H__
