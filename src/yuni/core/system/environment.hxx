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

	template<class AnyStringT> inline String Read(const AnyStringT& name)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, SystemEnvironment_InvalidTypeForString);

		return ::getenv(Traits::CString<UType>::Buffer(name));
	}

	template<class AnyStringT, class AnyStringT2>
	inline bool Read(const AnyStringT& name, AnyStringT2& out, const bool emptyBefore)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT2>::Type UTypeOut;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, SystemEnvironment_InvalidTypeForString);
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UTypeOut>::valid, SystemEnvironment_InvalidTypeForOutString);

		if (emptyBefore)
			out.clear();
		out += ::getenv(Traits::CString<UType>::Buffer(name));
		return true;
	}



} // namespace Environment
} // namespace System
} // namespace Yuni

#endif // __YUNI_CORE_SYSTEM_ENVIRONMENT_HXX__
