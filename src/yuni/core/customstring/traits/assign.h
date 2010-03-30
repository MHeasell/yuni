#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__

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
		static void Do(CustomStringT& s, const C& rhs)
		{
			// By Default, we will clear the buffer and then append the new content
			// Which is the standard behavior but may not the most efficient way
			s.clear();
			Yuni::Extension::CustomString::Append<CustomStringT, C>::Do(s, rhs);
		}
	};



	// std::string
	template<class CustomStringT, class TraitsT, class AllocT>
	struct Assign<CustomStringT, std::basic_string<typename CustomStringT::Type, TraitsT,AllocT> >
	{
		typedef std::basic_string<typename CustomStringT::Type, TraitsT,AllocT> S;
		static void Do(CustomStringT& s, const S& rhs)
		{
			if (!rhs.empty())
				s.assignWithoutChecking(rhs.c_str(), rhs.size());
			else
				s.clear();
		}
	};


	// Yuni::String
	template<class CustomStringT, int ChunkSizeT>
	struct Assign<CustomStringT, StringBase<typename CustomStringT::Type, ChunkSizeT> >
	{
		typedef StringBase<typename CustomStringT::Type, ChunkSizeT> S;
		static void Do(CustomStringT& s, const S& rhs)
		{
			if (rhs.notEmpty())
				s.assignWithoutChecking(rhs.c_str(), rhs.size());
			else
				s.clear();
		}
	};


	// C*
	template<class CustomStringT>
	struct Assign<CustomStringT, typename CustomStringT::Type*>
	{
		typedef typename CustomStringT::Type C;
		static void Do(CustomStringT& s, const C* rhs)
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
		static void Do(CustomStringT& s, const C rhs[N])
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
		static void Do(CustomStringT& s, const C rhs)
		{
			s.assignWithoutChecking(rhs);
		}
	};


	// CustomString
	template<class CustomStringT, unsigned int ChunkSizeT, bool ExpandT, bool ZeroT>
	struct Assign<CustomStringT, Yuni::CustomString<ChunkSizeT, ExpandT, ZeroT> >
	{
		typedef Yuni::CustomString<ChunkSizeT, ExpandT, ZeroT> C;
		static void Do(CustomStringT& s, const C& rhs)
		{
			if (rhs.notEmpty())
				s.assignWithoutChecking(rhs.data(), rhs.size());
			else
				s.clear();
		}
	};


	// nullptr
	template<class CustomStringT>
	struct Assign<CustomStringT, Yuni::NullPtr>
	{
		static void Do(CustomStringT& s, const Yuni::NullPtr&)
		{
			s.clear();
		}
	};



	// bool
	template<class CustomStringT>
	struct Assign<CustomStringT, bool>
	{
		static void Do(CustomStringT& s, const bool rhs)
		{
			if (rhs)
				s.assignWithoutChecking("true", 4);
			else
				s.assignWithoutChecking("false", 5);
		}
	};


# define YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(BUFSIZE, FORMAT, TYPE) \
	template<class CustomStringT> \
	struct Assign<CustomStringT, TYPE> \
	{ \
		static void Do(CustomStringT& s, const TYPE rhs) \
		{ \
			typename CustomStringT::Type buffer[BUFSIZE]; \
			(void) YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, BUFSIZE, FORMAT, rhs); \
			s.assignWithoutChecking(buffer, \
				Yuni::Traits::Length<typename CustomStringT::Type*, typename CustomStringT::Size>::Value(buffer)); \
		} \
	}


	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(24, "%lf", float);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(24, "%lf", double);




} // namespace CustomString
} // namespace Extension
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__
