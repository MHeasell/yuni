
#include "connector-data.h"
#include "../../thread/id.h"



namespace Yuni
{
namespace Private
{
namespace DBI
{


	ConnectorData::ConnectorData()
	{
	}


	ConnectorData::~ConnectorData()
	{
	}


	ChannelPtr ConnectorData::openChannel()
	{
		// lock
		Yuni::MutexLocker locker(mutex);

		Channel::Table::iterator i = channels.find(Thread::ID());

		// retrieving a channel to the remote database
		if (i != channels.end())
			return i->second;

		// otherwise we have to create a new channel
		return new Channel(settings);
	}





} // namespace DBI
} // namespace Private
} // namespace Yuni

