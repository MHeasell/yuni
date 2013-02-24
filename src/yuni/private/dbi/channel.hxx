#ifndef __YUNI_PRIVATE_DBI_CHANNEL_HXX__
# define __YUNI_PRIVATE_DBI_CHANNEL_HXX__



namespace Yuni
{
namespace Private
{
namespace DBI
{


	inline Yuni::DBI::Error Channel::begin(uint& handle)
	{
		if (!nestedTransactionCount++)
		{
			// No transaction available - creating a new one
		}
		else
		{
			// A transaction is already present - starting a savepoint
		}

		// The transaction handle will be the number of transaction
		handle = nestedTransactionCount;
		// no error
		return Yuni::DBI::errNone;
	}


	inline Yuni::DBI::Error Channel::rollback(uint handle)
	{
		if (handle != nestedTransactionCount || not handle)
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
