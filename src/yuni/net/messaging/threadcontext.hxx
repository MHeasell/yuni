#ifndef __YUNI_NET_MESSAGING_THREAD_CONTEXT_HXX__
# define __YUNI_NET_MESSAGING_THREAD_CONTEXT_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	inline Context::Context() :
		userdata(NULL)
	{
	}


	inline void Context::clear()
	{
		text.clear();
		clob.clear();
	}


	template<uint MaxSize, class StringT>
	inline void Context::AutoShrink(StringT& variable)
	{
		variable.clear();
		if (variable.capacity() > MaxSize)
			variable.shrink();
	}


	inline void Context::autoshrink()
	{
		AutoShrink<6 * 1024>(text);
		AutoShrink<5 * 1024 * 1024>(clob);
		AutoShrink<1 * 1024 * 1024>(buffer);
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_THREAD_CONTEXT_H__
