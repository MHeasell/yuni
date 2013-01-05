#ifndef __YUNI_NET_MESSAGING_SERVICE_HXX__
# define __YUNI_NET_MESSAGING_SERVICE_HXX__


namespace Yuni
{
namespace Net
{
namespace Messaging
{

	inline Error Service::Transports::add(const Port& port, Transport::ITransport::Ptr transport)
	{
		return add("*", port, transport);
	}




} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_SERVICE_HXX__
