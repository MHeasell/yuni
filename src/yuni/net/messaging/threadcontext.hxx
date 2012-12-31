#ifndef __YUNI_NET_MESSAGING_THREAD_CONTEXT_HXX__
# define __YUNI_NET_MESSAGING_THREAD_CONTEXT_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	inline ThreadContext::ThreadContext() :
		userdata(NULL)
	{
	}


	inline void ThreadContext::clear()
	{
		text.clear();
		clob.clear();
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__
