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


	inline bool Service::HeavyTasks::enabled() const
	{
		return pEnabled;
	}


	inline void Service::HeavyTasks::enabled(bool on)
	{
		pEnabled = (on ? 1 : 0);
	}





} // namespace Messaging
} // namespace Yuni

#endif // __YUNI_MESSAGING_SERVICE_HXX__
