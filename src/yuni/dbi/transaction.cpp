
#include "transaction.h"
#include "connector-pool.h"
#include "../private/dbi/connector-data.h"
#include "../private/dbi/channel.h"
#include <cassert>



namespace Yuni
{
namespace DBI
{

	Transaction::Transaction(Yuni::Private::DBI::ConnectorDataPtr& data)
	{
		// retrieving a channel to the remote database
		pChannel = data->openChannel();
		pChannel->mutex.lock();
	}


	Transaction::Transaction(const Transaction&)
	{
		// should never happen
		assert(false);
		exit(42); // throw
	}


	Transaction::~Transaction()
	{
		assert(pChannel and "Invalid channel but valid tx handle");

		// automatic rollback, if not already commited
		if (pTxHandle)
			pChannel->rollback(pTxHandle);
		pChannel->mutex.unlock();
	}


	Transaction& Transaction::operator = (const Transaction&)
	{
		// should never happen
		assert(false);
		exit(42); // thow
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

			pTxHandle = 0;
			return err;
		}
		return errNoTransaction;
	}


	DBI::Error Transaction::rollback()
	{
		if (pTxHandle)
		{
			assert(pChannel and "Invalid channel but valid tx handle");
			Error err = pChannel->rollback(pTxHandle);
			// reset
			pTxHandle = 0;
			return err;
		}
		return errNoTransaction;
	}


	DBI::Error Transaction::perform(const AnyString& script)
	{
		if (not pTxHandle)
		{
			DBI::Error err = pChannel->begin(pTxHandle);
			if (err != errNone)
				return err;
		}

		return errNone;
	}





} // namespace DBI
} // namespace Yuni

