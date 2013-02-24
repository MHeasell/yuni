#ifndef __YUNI_DBI_TRANSACTION_HiXX__
# define __YUNI_DBI_TRANSACTION_HXX__


namespace Yuni
{
namespace DBI
{


	inline Query Transaction::prepare(const AnyString& stmt)
	{
		return Query(stmt);
	}


	inline Query Transaction::operator () (const AnyString& stmt)
	{
		return Query(stmt);
	}





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_TRANSACTION_HXX__
