#ifndef __YUNI_CORE_SYSTEM_ENVIRONMENT_HXX__
# define __YUNI_CORE_SYSTEM_ENVIRONMENT_HXX__

# include "windows.hdr.h"
# include <stdlib.h>
# include "../traits/cstring.h"


namespace Yuni
{
namespace System
{
namespace Environment
{

	template<class StringT> inline String Read(const StringT& name)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<StringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, SystemEnvironment_InvalidTypeForString);

		return ::getenv(Traits::CString<UType>::Buffer(name));
	}

	template<class StringT, class StringT2>
	inline bool Read(const StringT& name, StringT2& out, const bool emptyBefore)
	{
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, SystemEnvironment_InvalidTypeForString);
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, SystemEnvironment_InvalidTypeForOutString);

		if (emptyBefore)
			out.clear();
		out += ::getenv(Traits::CString<StringT>::Buffer(name));
		return true;
	}



} // namespace Environment
} // namespace System
} // namespace Yuni

#endif // __YUNI_CORE_SYSTEM_ENVIRONMENT_HXX__
