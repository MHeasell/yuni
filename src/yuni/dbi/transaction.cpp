
#include "transaction.h"
#include "connector-pool.h"
#include "../private/dbi/connector-data.h"
#include "../private/dbi/channel.h"
#include <cassert>
#include "utils.h"



namespace Yuni
{
namespace DBI
{

	Transaction::Transaction(Yuni::Private::DBI::ConnectorDataPtr& data)
	{
		// retrieving or opening a channel to the remote database
		pChannel = data->openChannel();
		// avoid concurrent access to this channel
		pChannel->mutex.lock();
	}


	Transaction::Transaction(Yuni::Private::DBI::ChannelPtr& channel) :
		pChannel(channel),
		pTxHandle(0)
	{
		assert(!(!pChannel) and "null pointer to channel");
		pChannel->mutex.lock();
	}


	Transaction::~Transaction()
	{
		// the channel may have been reset by the move constructor
		if (!(!pChannel))
		{
			// automatic rollback, if not already commited
			if (pTxHandle)
				pChannel->rollback(pTxHandle);

			// allow concurrent access to the channel
			pChannel->mutex.unlock();
		}
	}


	DBI::Error Transaction::rebegin()
	{
		if (pTxHandle)
		{
			assert(pChannel and "Invalid channel but valid tx handle");
			pChannel->rollback(pTxHandle);
		}
		else
		{
			if (not pChannel)
			{
			}
		}

		// Starting a new transaction
		return pChannel->begin(pTxHandle);
	}


	DBI::Error Transaction::commit()
	{
		if (pTxHandle)
		{
			assert(pChannel and "Invalid channel but valid tx handle");
			Error err = pChannel->commit(pTxHandle);

			pTxHandle = nullHandle;
			return err;
		}
		return errNone;
	}


	DBI::Error Transaction::rollback()
	{
		if (pTxHandle)
		{
			assert(pChannel and "Invalid channel but valid tx handle");
			Error err = pChannel->rollback(pTxHandle);
			// reset
			pTxHandle = nullHandle;
			return err;
		}
		return errNone;
	}


	DBI::Error Transaction::perform(const AnyString& script)
	{
		if (not pTxHandle)
		{
			DBI::Error err = pChannel->begin(pTxHandle);
			if (err != errNone)
				return err;
		}

		return errNoTransaction;
	}


	DBI::Error Transaction::truncate(const AnyString& tablename)
	{
		if (not IsValidIdentifier(tablename))
			return errInvalidIdentifier;


		Yuni::Private::DBI::ChannelPtr channel = pChannel;
		if (!(!channel))
		{
			// the adapter
			::yn_dbi_adapter& adapter = channel->adapter;

			if (adapter.truncate)
				return (DBI::Error) adapter.truncate(tablename.c_str(), tablename.size());
		}

		// Fallback to a failsafe method
		// -- stmt << "TRUNCATE " << tablename << ';';
		CString<512, false> stmt;
		stmt << "DELETE FROM " << tablename << ';';
		return perform(stmt);
	}


	DBI::Error Transaction::vacuum()
	{
		Yuni::Private::DBI::ChannelPtr channel = pChannel;
		if (!(!channel))
		{
			// the adapter
			::yn_dbi_adapter& adapter = channel->adapter;

			if (adapter.vacuum)
				return (DBI::Error) adapter.vacuum();
		}

		// Fallback to the standard SQL command
		return perform("VACUUM;");
	}





} // namespace DBI
} // namespace Yuni

