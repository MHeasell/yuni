#ifndef __YUNI_PRIVATE_DBI_CHANNEL_HXX__
# define __YUNI_PRIVATE_DBI_CHANNEL_HXX__



namespace Yuni
{
namespace Private
{
namespace DBI
{

	inline void Channel::open()
	{
		// The inner mutex must be locked here

		if (not adapter.open or not adapter.close)
		{
			adapter.dbh = nullptr;
			status = Yuni::DBI::errInvalidAdapter;
		}
		else
		{
			if (adapter.dbh)
			{
				// a communication channel is already opened. Closing it.
				adapter.close(adapter.dbh);
			}

			// try to open a new communication channel
			auto error = (Yuni::DBI::Error) adapter.open(&adapter.dbh,
				settings.host.c_str(),      // host
				settings.port,              // port
				settings.username.c_str(),  // username
				settings.password.c_str(),  // password
				settings.database.c_str()   // database name
			);

			if (error != Yuni::DBI::errNone)
			{
				adapter.dbh = nullptr;
				status = error;
				return;
			}

			// ok, good to go
			status = Yuni::DBI::errNone;
		}
	}


	inline Yuni::DBI::Error Channel::begin(uint& handle)
	{
		using namespace Yuni::DBI;

		if (status != errNone)
		{
			// no connection to the remote database - retrying to connect
			open();
			if (status != errNone)
				return status;
		}

		if (0 == nestedTransactionCount++)
		{
			// No transaction available - creating a new one
			auto error = (Error) adapter.begin(adapter.dbh);
			if (error != errNone)
			{
				--nestedTransactionCount;
				return error;
			}
		}
		else
		{
			// A transaction is already present - starting a savepoint
			ShortString64 spname("__yn__sp_");
			spname <<  nestedTransactionCount;
			auto error = (Error) adapter.savepoint(adapter.dbh, spname.c_str(), spname.size());
			if (error != errNone)
			{
				--nestedTransactionCount;
				return error;
			}
		}

		// The transaction handle will be the number of transaction
		handle = nestedTransactionCount;
		// no error
		return errNone;
	}


	inline Yuni::DBI::Error Channel::rollback(uint handle)
	{
		assert(handle != 0 and "invalid handle");

		if (handle != nestedTransactionCount)
		{
			std::cerr << "\ninvalid transaction lifetime rollback" << std::endl;
			assert(false && "invalid transaction lifetime rollback");
			return Yuni::DBI::errInvalidNestedTransaction;
		}

		if (!--nestedTransactionCount)
		{
			// rollback the transaction
		}
		else
		{
			// rollbacking a savepoint
		}
		return Yuni::DBI::errNone;
	}


	inline Yuni::DBI::Error Channel::commit(uint handle)
	{
		assert(handle != 0 and "invalid handle");

		if (handle != nestedTransactionCount)
		{
			std::cerr << "\ninvalid transaction lifetime commit" << std::endl;
			assert(false && "invalid transaction lifetime commit");
			return Yuni::DBI::errInvalidNestedTransaction;
		}

		if (!--nestedTransactionCount)
		{
			// committing the transaction
		}
		else
		{
			// committing a savepoint
		}
		return Yuni::DBI::errNone;
	}






} // namespace DBI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_DBI_CHANNEL_HXX__
