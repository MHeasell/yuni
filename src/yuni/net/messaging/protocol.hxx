#ifndef __YUNI_NET_MESSAGING_PROTOCOL_HXX__
# define __YUNI_NET_MESSAGING_PROTOCOL_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	inline Schema& Protocol::schema()
	{
		return pSchemas[(pTmp.clear())];
	}


	inline Schema& Protocol::schema(const AnyString& name)
	{
		return pSchemas[(pTmp = name)];
	}





} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_PROTOCOL_HXX__
