#ifndef __YUNI_DBI_COLUMN_HXX__
# define __YUNI_DBI_COLUMN_HXX__



namespace Yuni
{
namespace DBI
{

	inline Column::Column(::yn_dbi_adapter& adapter, void* handle, uint colindx) :
		pAdapter(adapter),
		pHandle(handle),
		pColumnIndex(colindx)
	{}

	inline Column::Column(const Column& rhs) :
		pAdapter(rhs.pAdapter),
		pHandle(rhs.pHandle),
		pColumnIndex(rhs.pColumnIndex)
	{}


	inline bool Column::null()
	{
		return (0 != pAdapter.column_is_null(pHandle, pColumnIndex));
	}

	inline String Column::asString()
	{
		uint length;
		const char* text = pAdapter.column_to_cstring(pHandle, pColumnIndex, &length);
		return String(text, length);
	}

	template<class StringT>
	inline void Column::appendToString(StringT& string)
	{
		uint length;
		const char* text = pAdapter.column_to_cstring(pHandle, pColumnIndex, &length);
		string.append(text, length);
	}


	inline bool Column::asBool()
	{
		return (0 != pAdapter.column_to_int32(pHandle, pColumnIndex));
	}

	inline double Column::asDouble()
	{
		return pAdapter.column_to_double(pHandle, pColumnIndex);
	}

	inline sint32 Column::asInt()
	{
		return pAdapter.column_to_int32(pHandle, pColumnIndex);
	}

	inline sint64 Column::asInt64()
	{
		return pAdapter.column_to_int64(pHandle, pColumnIndex);
	}




	template<class T>
	inline T Column::as()
	{
		const String& text = asString();
		return text.to<T>();
	}


	template<> inline String Column::as<String>()
	{
		return asString();
	}

	template<> inline bool Column::as<bool>()
	{
		return asBool();
	}

	template<> inline double Column::as<double>()
	{
		return asDouble();
	}

	template<> inline float Column::as<float>()
	{
		return (float) asDouble();
	}

	template<> inline sint32 Column::as<sint32>()
	{
		return asInt();
	}

	template<> inline sint64 Column::as<sint64>()
	{
		return asInt64();
	}






} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_COLUMN_HXX__
