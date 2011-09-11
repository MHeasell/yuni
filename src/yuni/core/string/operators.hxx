#ifndef __YUNI_CORE_STRING_OPERATORS_H__
# define __YUNI_CORE_STRING_OPERATORS_H__




//! \name Operator overload for stream printing
//@{

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline std::ostream& operator << (std::ostream& out, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	out.write(rhs.data(), static_cast<std::streamsize>(rhs.size()));
	return out;
}

inline std::ostream& operator << (std::ostream& out, const Yuni::UTF8::Char& rhs)
{
	rhs.write(out);
	return out;
}





template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CString<SizeT,ExpT,ZeroT>& rhs, const char* const u)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CString<SizeT,ExpT,ZeroT>& rhs, const wchar_t* u)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CString<SizeT,ExpT,ZeroT>& rhs, const char u)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CString<SizeT,ExpT,ZeroT>& rhs, const wchar_t u)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(rhs) += u;
}



template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const wchar_t* u, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const char* const u, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const char u, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const wchar_t u, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(u) += rhs;
}




template<unsigned int SizeT, bool ExpT,bool ZeroT, class TraitsT, class AllocT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const std::basic_string<char,TraitsT,AllocT>& u, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(u) += rhs;
}


template<unsigned int SizeT, bool ExpT,bool ZeroT, class TraitsT, class AllocT>
inline Yuni::CString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CString<SizeT,ExpT,ZeroT>& rhs, const std::basic_string<char,TraitsT,AllocT>& u)
{
	return Yuni::CString<SizeT,ExpT,ZeroT>(rhs) += u;
}


template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator == (const char* lhs, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs == lhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator != (const char* lhs, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs != lhs;
}

template<int N, unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator == (const char lhs[N], const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs == lhs;
}

template<int N, unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator != (const char lhs[N], const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs != lhs;
}

template<class TraitsT, class AllocT, unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator == (const std::basic_string<char,TraitsT,AllocT>& lhs, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs == lhs;
}

template<class TraitsT, class AllocT, unsigned int SizeT, bool ExpT,bool ZeroT>
inline bool
operator != (const std::basic_string<char,TraitsT,AllocT>& lhs, const Yuni::CString<SizeT,ExpT,ZeroT>& rhs)
{
	return rhs != lhs;
}


//@}


#endif // __YUNI_CORE_STRING_OPERATORS_H__
