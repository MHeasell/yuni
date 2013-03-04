#ifndef __YUNI_DBI_QUERY_BUILDER_HXX__
# define __YUNI_DBI_QUERY_BUILDER_HXX__


namespace Yuni
{
namespace DBI
{

	inline QueryBuilder::QueryBuilder(QueryBuilder&& other) :
		pAdapter(other.pAdapter),
		pHandle(other.pHandle),
		pRowCount(other.pRowCount)
	{
		other.pHandle = nullptr;
		other.pRowCount = 0;
	}


	inline QueryBuilder::~QueryBuilder()
	{
		if (pHandle)
			pAdapter.query_ref_release(pHandle);
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, const AnyString& value)
	{
		if (pHandle)
			pAdapter.bind_str(pHandle, index, value.c_str(), value.size());
		return *this;
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, bool value)
	{
		if (pHandle)
			pAdapter.bind_bool(pHandle, index, (int) value);
		return *this;
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, sint32 value)
	{
		if (pHandle)
			pAdapter.bind_int32(pHandle, index, value);
		return *this;
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, sint64 value)
	{
		if (pHandle)
			pAdapter.bind_int64(pHandle, index, value);
		return *this;
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, double value)
	{
		if (pHandle)
			pAdapter.bind_double(pHandle, index, value);
		return *this;
	}


	inline QueryBuilder& QueryBuilder::bind(uint index, const NullPtr&)
	{
		if (pHandle)
			pAdapter.bind_null(pHandle, index);
		return *this;
	}


	template<class A1>
	inline QueryBuilder&
	QueryBuilder::map(const A1& a1)
	{
		(void) bind(0, a1);
		return *this;
	}


	template<class A1, class A2>
	inline QueryBuilder&
	QueryBuilder::map(const A1& a1, const A2& a2)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		return *this;
	}


	template<class A1, class A2, class A3>
	inline QueryBuilder&
	QueryBuilder::map(const A1& a1, const A2& a2, const A3& a3)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		(void) bind(2, a3);
		return *this;
	}


	template<class A1, class A2, class A3, class A4>
	inline QueryBuilder&
	QueryBuilder::map(const A1& a1, const A2& a2, const A3& a3, const A4& a4)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		(void) bind(2, a3);
		(void) bind(3, a4);
		return *this;
	}


	inline bool QueryBuilder::empty() const
	{
		return (0 == pRowCount);
	}


	inline uint64 QueryBuilder::rowCount() const
	{
		return pRowCount;
	}


	inline DBI::Error QueryBuilder::next()
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to_next(pHandle)
			: DBI::errNoRow;
	}


	inline DBI::Error QueryBuilder::previous()
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to_previous(pHandle)
			: DBI::errNoRow;
	}


	inline DBI::Error QueryBuilder::moveTo(uint64 rowindex)
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to(pHandle, rowindex)
			: DBI::errNoRow;
	}


	template<class CallbackT>
	inline DBI::Error QueryBuilder::each(const CallbackT& callback)
	{
		DBI::Error error = next();
		return error;
	}




} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_QUERY_BUILDER_HXX__
