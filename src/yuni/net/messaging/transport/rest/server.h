#ifndef __YUNI_NET_MESSAGING_TRANSPORT_REST_SERVER_H__
# define __YUNI_NET_MESSAGING_TRANSPORT_REST_SERVER_H__

# include "../transport.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace Transport
{
namespace REST
{

	class Server final : public ITransport
	{
	public:
		//! Opaque structure for Internal data related to the rest server
		class ServerData;

	public:
		//! Default constructor
		Server();
		//! Destructor
		virtual ~Server();

		virtual Net::Error  start() override;

		virtual Net::Error  run() override;

		virtual void stop() override;

		virtual void protocol(const Protocol& protocol) override;

	private:
		void wait();

	private:
		//! Internal data
		ServerData* pData;

	}; // class Server





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni

#endif // __YUNI_NET_MESSAGING_TRANSPORT_REST_SERVER_H__
