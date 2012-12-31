#ifndef __YUNI_NET_MESSAGING_API_SCHEMA_HXX__
# define __YUNI_NET_MESSAGING_API_SCHEMA_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	inline void Schema::shrinkMemory()
	{
		methods.shrinkMemory();
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni


#endif // __YUNI_NET_MESSAGING_API_SCHEMA_HXX__
