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
		return pSchemas[(pTmp = "/")];
	}


	inline Schema& Protocol::schema(const AnyString& name)
	{
		return pSchemas[(pTmp = name)];
	}


	inline const Schema::Hash& Protocol::allSchemas() const
	{
		return pSchemas;
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_PROTOCOL_HXX__
