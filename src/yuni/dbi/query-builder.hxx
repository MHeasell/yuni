#ifndef __YUNI_DBI_QUERY_BUILDER_HXX__
# define __YUNI_DBI_QUERY_BUILDER_HXX__


namespace Yuni
{
namespace DBI
{

	inline PreparedStatement::PreparedStatement(::yn_dbi_adapter& adapter, void* handle) :
		pAdapter(adapter),
		pHandle(handle),
		pRowCount()
	{
	}


	inline PreparedStatement::PreparedStatement(PreparedStatement&& other) :
		pAdapter(other.pAdapter),
		pHandle(other.pHandle),
		pRowCount(other.pRowCount)
	{
		other.pHandle = nullptr;
		other.pRowCount = 0;
	}


	inline PreparedStatement::~PreparedStatement()
	{
		if (pHandle)
			pAdapter.query_ref_release(pHandle);
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, const AnyString& value)
	{
		if (pHandle)
			pAdapter.bind_str(pHandle, index, value.c_str(), value.size());
		return *this;
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, bool value)
	{
		if (pHandle)
			pAdapter.bind_bool(pHandle, index, (int) value);
		return *this;
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, sint32 value)
	{
		if (pHandle)
			pAdapter.bind_int32(pHandle, index, value);
		return *this;
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, sint64 value)
	{
		if (pHandle)
			pAdapter.bind_int64(pHandle, index, value);
		return *this;
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, double value)
	{
		if (pHandle)
			pAdapter.bind_double(pHandle, index, value);
		return *this;
	}


	inline PreparedStatement& PreparedStatement::bind(uint index, const NullPtr&)
	{
		if (pHandle)
			pAdapter.bind_null(pHandle, index);
		return *this;
	}


	template<class A1>
	inline PreparedStatement&
	PreparedStatement::map(const A1& a1)
	{
		(void) bind(0, a1);
		return *this;
	}


	template<class A1, class A2>
	inline PreparedStatement&
	PreparedStatement::map(const A1& a1, const A2& a2)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		return *this;
	}


	template<class A1, class A2, class A3>
	inline PreparedStatement&
	PreparedStatement::map(const A1& a1, const A2& a2, const A3& a3)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		(void) bind(2, a3);
		return *this;
	}


	template<class A1, class A2, class A3, class A4>
	inline PreparedStatement&
	PreparedStatement::map(const A1& a1, const A2& a2, const A3& a3, const A4& a4)
	{
		(void) bind(0, a1);
		(void) bind(1, a2);
		(void) bind(2, a3);
		(void) bind(3, a4);
		return *this;
	}


	inline bool PreparedStatement::empty() const
	{
		return (0 == pRowCount);
	}


	inline uint64 PreparedStatement::rowCount() const
	{
		return pRowCount;
	}


	inline DBI::Error PreparedStatement::next()
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to_next(pHandle)
			: DBI::errNoRow;
	}


	inline DBI::Error PreparedStatement::previous()
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to_previous(pHandle)
			: DBI::errNoRow;
	}


	inline DBI::Error PreparedStatement::moveTo(uint64 rowindex)
	{
		return (pHandle)
			? (DBI::Error) pAdapter.cursor_go_to(pHandle, rowindex)
			: DBI::errNoRow;
	}


	template<class CallbackT>
	inline DBI::Error PreparedStatement::each(const CallbackT& callback)
	{
		auto error = next();
		if (not error)
		{
			do
			{
		//		if (not callback(fetch()))
		//			return;
			}
			while (DBI::errNone == (error = next()));
		}
		return error;
	}




} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_QUERY_BUILDER_HXX__
