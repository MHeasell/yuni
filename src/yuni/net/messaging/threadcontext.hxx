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


	template<uint MaxSize, class StringT>
	inline void ThreadContext::AutoShrink(StringT& variable)
	{
		variable.clear();
		if (variable.capacity() > MaxSize)
			variable.shrink();
	}


	inline void ThreadContext::autoshrink()
	{
		AutoShrink<6 * 1024>(text);
		AutoShrink<5 * 1024 * 1024>(clob);
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__
