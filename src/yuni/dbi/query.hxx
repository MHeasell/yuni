#ifndef __YUNI_DBI_QUERY_HXX__
# define __YUNI_DBI_QUERY_HXX__


namespace Yuni
{
namespace DBI
{

	inline Query::Query(const AnyString& stmt) :
		pStmt(stmt)
	{}


	template<class CallbackCursorT>
	inline bool Query::each(const CallbackCursorT& callback)
	{
		return execute().each(callback);
	}




} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_QUERY_HXX__
