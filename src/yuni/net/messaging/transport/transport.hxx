#ifndef __YUNI_NET_MESSAGING_TRANSPORT_TRANSPORT_HXX__
# define __YUNI_NET_MESSAGING_TRANSPORT_TRANSPORT_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace Transport
{


	inline ITransport::ITransport(Mode m) :
		mode(m),
		pAttachedThread(NULL)
	{
		// do nothing
	}


	inline ITransport::~ITransport()
	{
		// do nothing
	}


	inline Thread::IThread*  ITransport::attachedThread()
	{
		return pAttachedThread;
	}


	inline const Thread::IThread*  ITransport::attachedThread() const
	{
		return pAttachedThread;
	}


	inline void ITransport::attachedThread(Thread::IThread* thread)
	{
		pAttachedThread = thread;
	}






} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_TRANSPORT_TRANSPORT_HXX__
