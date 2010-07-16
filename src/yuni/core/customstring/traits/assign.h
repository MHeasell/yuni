#ifndef __YUNI_CORE_CUSTOM_STRING_TRAITS_ASSIGN_H__
# define __YUNI_CORE_CUSTOM_STRING_TRAITS_ASSIGN_H__

# include "../../traits/length.h"

namespace Yuni
{
namespace Extension
{
namespace CustomString
{


	template<class CustomStringT, class C>
	struct Assign
	{
		static void Perform(CustomStringT& s, const C& rhs)
		{
			// By Default, we will clear the buffer and then append the new content
			// Which is the standard behavior but may not the most efficient way
			s.clear();
			Yuni::Extension::CustomString::Append<CustomStringT, C>::Perform(s, rhs);
		}
	};



	// C*
	template<class CustomStringT>
	struct Assign<CustomStringT, typename CustomStringT::Type*>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(CustomStringT& s, const C* rhs)
		{
			if (rhs)
				s.assignWithoutChecking(rhs, Yuni::Traits::Length<C*, typename CustomStringT::Size>::Value(rhs));
			else
				s.clear();
		}
	};


	// C[N]
	template<class CustomStringT, int N>
	struct Assign<CustomStringT, typename CustomStringT::Type[N]>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(CustomStringT& s, const C rhs[N])
		{
			if (N > 0)
			{
				// The calculation with `N` is required to properly handle
				// both a zero-terminated buffer and a simple array
				s.assignWithoutChecking(rhs, N - ((rhs[N-1] == C()) ? 1 : 0));
			}
			else
				s.clear();
		}
	};


	// C
	template<class CustomStringT>
	struct Assign<CustomStringT, typename CustomStringT::Type>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(CustomStringT& s, const C rhs)
		{
			s.assignWithoutChecking(rhs);
		}
	};


	// nullptr
	template<class CustomStringT>
	struct Assign<CustomStringT, Yuni::NullPtr>
	{
		static void Perform(CustomStringT& s, const Yuni::NullPtr&)
		{
			s.clear();
		}
	};



	// bool
	template<class CustomStringT>
	struct Assign<CustomStringT, bool>
	{
		static void Perform(CustomStringT& s, const bool rhs)
		{
			if (rhs)
				s.assignWithoutChecking("true", 4);
			else
				s.assignWithoutChecking("false", 5);
		}
	};




# ifdef YUNI_OS_MSVC
# 	define YUNI_PRIVATE_CUSTOMSTR_SPRINTF(BUFFER, BUFSIZE, FORMAT, VALUE)  sprintf_s(BUFFER, BUFSIZE,FORMAT,VALUE)
# else
# 	define YUNI_PRIVATE_CUSTOMSTR_SPRINTF(BUFFER, BUFSIZE, FORMAT, VALUE)  snprintf(BUFFER, BUFSIZE,FORMAT,VALUE)
# endif

# define YUNI_PRIVATE_CUSTOM_STRING_ASSIGN_IMPL(BUFSIZE, FORMAT, TYPE) \
	template<class CustomStringT> \
	struct Assign<CustomStringT, TYPE> \
	{ \
		static void Perform(CustomStringT& s, const TYPE rhs) \
		{ \
			typename CustomStringT::Type buffer[BUFSIZE]; \
			(void) YUNI_PRIVATE_CUSTOMSTR_SPRINTF(buffer, BUFSIZE, FORMAT, rhs); \
			s.assignWithoutChecking(buffer, \
				Yuni::Traits::Length<typename CustomStringT::Type*, typename CustomStringT::Size>::Value(buffer)); \
		} \
	}


	YUNI_PRIVATE_CUSTOM_STRING_ASSIGN_IMPL(24, "%lf", float);
	YUNI_PRIVATE_CUSTOM_STRING_ASSIGN_IMPL(24, "%lf", double);


# undef YUNI_PRIVATE_CUSTOMSTR_SPRINTF
# undef YUNI_PRIVATE_CUSTOM_STRING_ASSIGN_IMPL


} // namespace CustomString
} // namespace Extension
} // namespace Yuni

#endif // __YUNI_CORE_CUSTOM_STRING_TRAITS_ASSIGN_H__
