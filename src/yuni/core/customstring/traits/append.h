#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__

# include "../../traits/length.h"
# include "integer.h"
# include <stdio.h>

# ifdef YUNI_OS_MSVC
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::sprintf_s(BUFFER,SIZE,F,V)
# else
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::snprintf(BUFFER,SIZE,F,V)
# endif


namespace Yuni
{
namespace Extension
{
namespace CustomString
{

	template<class CustomStringT, class C>
	struct Append
	{
		// Unknown type
		YUNI_STATIC_ASSERT(false, CustomString_AppendUnknownType);
	};


	// C*
	template<class CustomStringT>
	struct Append<CustomStringT, char*>
	{
		typedef typename CustomStringT::Type TypeC;
		typedef typename Static::Remove::Const<TypeC>::Type C;
		static void Perform(CustomStringT& s, const C* rhs)
		{
			if (rhs)
				s.appendWithoutChecking(rhs, Yuni::Traits::Length<C*,typename CustomStringT::Size>::Value(rhs));
		}
	};

	// C[N]
	template<class CustomStringT, int N>
	struct Append<CustomStringT, char[N]>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(CustomStringT& s, const C rhs[N])
		{
			if (N > 0)
			{
				// The calculation with `N` is required to properly handle
				// both a zero-terminated buffer and a simple array
				s.appendWithoutChecking(rhs, N - ((rhs[N-1] == C()) ? 1 : 0));
			}
		}
	};

	// C
	template<class CustomStringT>
	struct Append<CustomStringT, char>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(CustomStringT& s, const C rhs)
		{
			s.appendWithoutChecking(rhs);
		}
	};


	// nullptr
	template<class CustomStringT>
	struct Append<CustomStringT, Yuni::NullPtr>
	{
		static void Perform(CustomStringT& s, const Yuni::NullPtr&)
		{ /* Do nothing */ }
	};


	// bool
	template<class CustomStringT>
	struct Append<CustomStringT, bool>
	{
		static void Perform(CustomStringT& s, const bool rhs)
		{
			if (rhs)
				s.appendWithoutChecking("true", 4);
			else
				s.appendWithoutChecking("false", 5);
		}
	};


	// void*
	template<class CustomStringT>
	struct Append<CustomStringT, void*>
	{
		static void Perform(CustomStringT& s, const void* rhs)
		{
			typename CustomStringT::Type buffer[32];
			// On Windows, it may return a negative value
			if (YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, sizeof(buffer), "%p", rhs) >= 0)
			{
				s.appendWithoutChecking(buffer,
					Yuni::Traits::Length<typename CustomStringT::Type*, typename CustomStringT::Size>::Value(buffer));
			}
		}
	};



# define YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(BUFSIZE, FORMAT, TYPE) \
	template<class CustomStringT> \
	struct Append<CustomStringT, TYPE> \
	{ \
		static void Perform(CustomStringT& s, const TYPE rhs) \
		{ \
			typename CustomStringT::Type buffer[BUFSIZE]; \
			/* On Windows, it may returns a negative value */ \
			if (YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, BUFSIZE, FORMAT, rhs) >= 0) \
			{ \
				s.appendWithoutChecking(buffer, \
					Yuni::Traits::Length<typename CustomStringT::Type*, typename CustomStringT::Size>::Value(buffer)); \
			} \
		} \
	}

# define YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(TYPE) \
	template<class CustomStringT> \
	struct Append<CustomStringT, TYPE> \
	{ \
		static void Perform(CustomStringT& s, const TYPE rhs) \
		{ \
			Yuni::Private::CustomStringImpl::From<Math::Base::Decimal, TYPE>::AppendTo(s, rhs); \
		} \
	}


	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(sint16);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(sint32);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(sint64);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(uint16);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(uint32);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(uint64);
	# ifdef YUNI_HAS_LONG
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(long);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(unsigned long);
	# endif

	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(256, "%lf",  float);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(256, "%lf",  double);



} // namespace CustomString
} // namespace Extension
} // namespace Yuni

# undef YUNI_PRIVATE_MEMBUF_SPTRINF

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
