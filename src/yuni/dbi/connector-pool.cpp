
#include "connector-pool.h"
#include "../private/dbi/connector-data.h"



namespace Yuni
{
namespace DBI
{

	ConnectorPool::ConnectorPool(const ConnectorPool& rhs) :
		pData(rhs.pData)
	{
	}


	ConnectorPool::ConnectorPool()
	{
		// does nothing
	}


	ConnectorPool::~ConnectorPool()
	{
		close();
	}


	Error ConnectorPool::open(Adapter::IAdapter* adapter, const Settings& settings)
	{
		// close all existing connectionss if possible
		close();

		if (not adapter)
		{
			delete adapter;
			return errInvalidAdapter;
		}

		// new connector data
		auto* data = new Yuni::Private::DBI::ConnectorData(settings, adapter);

		// attempt to open a new channel
		{
			auto channel = data->openChannel();
			// should never happen, but we never know
			assert(!(!channel) and "invalid channel");
			if (not channel)
			{
				delete data;
				return errConnectionFailed;
			}

			// lock concurrent acces to the channel
			MutexLocker locker(channel->mutex);

			if (errNone != channel->status)
			{
				delete data;
				return channel->status;
			}
		}

		// ok - installing the new connector data
		Yuni::Private::DBI::ConnectorDataPtr smartdata(data);
		pData.swap(smartdata);
		return errNone;
	}


	void ConnectorPool::close()
	{
		Yuni::Private::DBI::ConnectorDataPtr data;
		data.swap(pData);
		if (!(!data))
		{
			// try to kill all possible connections which can be possibly closed
			// (aka all connections which are no longer in use)
			uint dummy;
			data->closeTooOldChannels(0, dummy);
		}
	}


	bool ConnectorPool::retrieveSettings(Settings& out) const
	{
		Yuni::Private::DBI::ConnectorDataPtr data = pData;
		if (!(!data))
		{
			out = data->settings;
			return true;
		}
		else
		{
			out.clear();
			return false;
		}
	}


	void ConnectorPool::closeIdleConnections(uint* remainingCount, uint* closedCount)
	{
		Yuni::Private::DBI::ConnectorDataPtr data = pData;
		if (!(!data))
		{
			// idle time
			uint idletime = data->settings.idleTime;

			uint statsRemain = 0;
			uint statsClosed = data->closeTooOldChannels(idletime, statsRemain);

			if (remainingCount)
				*remainingCount = statsRemain;
			if (closedCount)
				*closedCount = statsClosed;
		}
		else
		{
			if (remainingCount)
				*remainingCount = 0;
			if (closedCount)
				*closedCount = 0;
		}
	}


	void ConnectorPool::closeIdleConnections(uint maxIdleTime, uint* remainingCount, uint* closedCount)
	{
		Yuni::Private::DBI::ConnectorDataPtr data = pData;
		if (!(!data))
		{
			uint statsRemain = 0;
			uint statsClosed = data->closeTooOldChannels(maxIdleTime, statsRemain);

			if (remainingCount)
				*remainingCount = statsRemain;
			if (closedCount)
				*closedCount = statsClosed;
		}
		else
		{
			if (remainingCount)
				*remainingCount = 0;
			if (closedCount)
				*closedCount = 0;
		}
	}





} // namespace DBI
} // namespace Yuni


