#ifndef __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__
# define __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__

# include "../../dbi/settings.h"
# include "../../dbi/fwd.h"
# include "channel.h"



namespace Yuni
{
namespace Private
{
namespace DBI
{


	class ConnectorData final
	{
	public:
		ConnectorData();

		~ConnectorData();

		/*!
		** \brief Open a communication channel to the remote database
		*/
		ChannelPtr openChannel();


	public:
		//! Settings used to connect to the database
		Yuni::DBI::Settings settings;
		//! Mutex
		Mutex mutex;

		//! All channels, ordered by a thread id
		Channel::Table channels;

	}; // class ConnectorData





} // namespace DBI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__
