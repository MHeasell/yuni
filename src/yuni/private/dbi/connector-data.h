#ifndef __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__
# define __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__

# include "../../dbi/settings.h"
# include "../../dbi/fwd.h"
# include "../../dbi/adapter/entries.h"
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

		/*!
		** \brief Close all old channels
		**
		** \param[out] remainingCount The number of channels currently opened (after cleanup)
		** \return The number of channels which have been closed
		*/
		uint closeTooOldChannels(uint& remainingCount);


	public:
		//! Settings used to connect to the database
		Yuni::DBI::Settings settings;
		//! Adapter Entries
		::yn_dbi_adapter adapter;
		//! Mutex
		Mutex mutex;

		//! All channels, ordered by a thread id
		Channel::Table channels;

	}; // class ConnectorData





} // namespace DBI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_DBI_CONNECTOR_DATA_H__
