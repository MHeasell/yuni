#ifndef __YUNI_MESSAGING_SERVICE_HXX__
# define __YUNI_MESSAGING_SERVICE_HXX__


namespace Yuni
{
namespace Messaging
{

	inline Net::Error Service::Transports::add(const Net::Port& port, Transport::ITransport::Ptr transport)
	{
		return add("*", port, transport);
	}




} // namespace Messaging
} // namespace Yuni

#endif // __YUNI_MESSAGING_SERVICE_HXX__
