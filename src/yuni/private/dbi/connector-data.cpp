
#include "connector-data.h"
#include "../../thread/id.h"
#include "../../datetime/timestamp.h"



namespace Yuni
{
namespace Private
{
namespace DBI
{


	ConnectorData::ConnectorData()
	{
		// reset adapter
		::memset(&adapter, '\0', sizeof(adapter));
	}


	ConnectorData::~ConnectorData()
	{
	}


	ChannelPtr ConnectorData::openChannel()
	{
		// current thread id
		uint64 tid = Thread::ID();

		// locker
		Yuni::MutexLocker locker(mutex);

		// checking if a channel does not already exists
		Channel::Table::iterator i = channels.find(tid);
		if (i != channels.end())
			return i->second;

		// otherwise we have to create a new one
		ChannelPtr newchan = new Channel(settings, adapter);
		channels[tid] = newchan;
		return newchan;
	}


	uint ConnectorData::closeTooOldChannels(uint& remainingCount)
	{
		// the current timestamp
		sint64 now = Yuni::DateTime::Now();
		// the number of channel which have been removed
		uint removedCount = 0;

		// avoid concurrent access
		Yuni::MutexLocker locker(mutex);

		// checking each channel
		Channel::Table::iterator it = channels.begin();
		while (it != channels.end())
		{
			// the channel itself
			Channel& channel = *(it->second);

			// we will first check the idle time of the channel, before
			// locking its own mutex

			// beware : the variable `lastUsed` might be in the future in comparison
			// of our variable `now`, since it can be modified without locking
			// our variable `mutex`
			if (now > channel.lastUsed)
			{
				// checking idle time
				if (settings.idleTime < (now - channel.lastUsed))
				{
					// our channel may be idle for too long
					// checking if it is not currently in use
					if (channel.mutex.trylock())
					{
						// it is safe to unlock here since no transaction can lock it
						// (our own mutex is already locked)
						channel.mutex.unlock();
						// removing the channel
						channels.erase(it++);
						// statistics
						++removedCount;
						// iterate
						continue;
					}
					else
					{
						// currently in use
					}

				} // idle time check
			} // future check

			// next channel
			++it;
		}

		// the thread which would periodically check for idle channels might
		// be no longer necessary. This variable will be the indicator
		remainingCount = (uint) channels.size();

		// return the number of dead channels
		return removedCount;
	}





} // namespace DBI
} // namespace Private
} // namespace Yuni

