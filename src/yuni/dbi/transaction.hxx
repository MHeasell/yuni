#ifndef __YUNI_DBI_TRANSACTION_HiXX__
# define __YUNI_DBI_TRANSACTION_HXX__


namespace Yuni
{
namespace DBI
{

	inline Transaction::Transaction(Transaction&& other) :
		pTxHandle(other.pTxhandle)
	{
		pChannel.swap(other.pChannel);
		other.pTxHandle = nullHandle;
	}


	inline Transaction&& Transaction::savepoint()
	{
		return Transaction(pChannel);
	}


	inline PreparedStatement&& Transaction::operator () (const AnyString& stmt)
	{
		return prepare(stmt);
	}





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_TRANSACTION_HXX__
