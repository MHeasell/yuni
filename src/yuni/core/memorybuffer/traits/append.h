#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__

# include "../../traits/length.h"
# include "integer.h"

# ifdef YUNI_OS_MSVC
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::sprintf_s(BUFFER,SIZE,F,V)
# else
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::sprintf(BUFFER,F,V)
# endif



namespace Yuni
{
namespace Private
{
namespace IStringImpl
{

	template<class MemBufT, class C>
	struct Append
	{
		// Unknown type
		YUNI_STATIC_ASSERT(false, IString_AppendUnknownType);
	};


	// std::string
	template<class MemBufT, class TraitsT, class AllocT>
	struct Append<MemBufT, std::basic_string<typename MemBufT::Type, TraitsT,AllocT> >
	{
		typedef std::basic_string<typename MemBufT::Type, TraitsT,AllocT> S;
		static void Do(MemBufT& memoryBuffer, const S& rhs)
		{
			if (!rhs.empty())
				memoryBuffer.appendWithoutChecking(rhs.c_str(), rhs.size());
		}
	};

	// yuni::string
	template<class MemBufT, int ChunkSizeT>
	struct Append<MemBufT, StringBase<typename MemBufT::Type, ChunkSizeT> >
	{
		typedef StringBase<typename MemBufT::Type, ChunkSizeT> S;
		static void Do(MemBufT& memoryBuffer, const S& rhs)
		{
			if (rhs.notEmpty())
				memoryBuffer.appendWithoutChecking(rhs.c_str(), rhs.size());
		}
	};


	// C*
	template<class MemBufT>
	struct Append<MemBufT, typename MemBufT::Type*>
	{
		typedef typename MemBufT::Type TypeC;
		typedef typename Static::Remove::Const<TypeC>::Type C;
		static void Do(MemBufT& memoryBuffer, const C* rhs)
		{
			if (rhs)
				memoryBuffer.appendWithoutChecking(rhs, Yuni::Core::Traits::Length<C*,typename MemBufT::Size>::Value(rhs));
		}
	};

	// C[N]
	template<class MemBufT, int N>
	struct Append<MemBufT, typename MemBufT::Type[N]>
	{
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C rhs[N])
		{
			if (N > 0)
			{
				// The calculation with `N` is required to properly handle
				// both a zero-terminated buffer and a simple array
				memoryBuffer.appendWithoutChecking(rhs, N - ((rhs[N-1] == C()) ? 1 : 0));
			}
		}
	};

	// C
	template<class MemBufT>
	struct Append<MemBufT, typename MemBufT::Type>
	{
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C rhs)
		{
			memoryBuffer.appendWithoutChecking(rhs);
		}
	};


	// IString
	template<class MemBufT, unsigned int ChunkSizeT, bool ExpandT, bool ZeroT>
	struct Append<MemBufT, Yuni::IString<typename MemBufT::Type, ChunkSizeT, ExpandT, ZeroT> >
	{
		typedef Yuni::IString<typename MemBufT::Type, ChunkSizeT, ExpandT, ZeroT> C;
		static void Do(MemBufT& memoryBuffer, const C& rhs)
		{
			if (rhs.notEmpty())
				memoryBuffer.appendWithoutChecking(rhs.data(), rhs.size());
		}
	};


	// nullptr
	template<class MemBufT>
	struct Append<MemBufT, Yuni::NullPtr>
	{
		static void Do(MemBufT& memoryBuffer, const Yuni::NullPtr&)
		{ /* Do nothing */ }
	};


	// bool
	template<class MemBufT>
	struct Append<MemBufT, bool>
	{
		static void Do(MemBufT& memoryBuffer, const bool rhs)
		{
			if (rhs)
				memoryBuffer.appendWithoutChecking("true", 4);
			else
				memoryBuffer.appendWithoutChecking("false", 5);
		}
	};


	// void*
	template<class MemBufT>
	struct Append<MemBufT, void*>
	{
		static void Do(MemBufT& memoryBuffer, const void* rhs)
		{
			typename MemBufT::Type buffer[20];
			(void) YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, sizeof(buffer), "%p", rhs);
			memoryBuffer.appendWithoutChecking(buffer,
				Yuni::Core::Traits::Length<typename MemBufT::Type*, typename MemBufT::Size>::Value(buffer));
		}
	};



# define YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(BUFSIZE, FORMAT, TYPE) \
	template<class MemBufT> \
	struct Append<MemBufT, TYPE> \
	{ \
		static void Do(MemBufT& memoryBuffer, const TYPE rhs) \
		{ \
			typename MemBufT::Type buffer[BUFSIZE]; \
			(void) YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, BUFSIZE, FORMAT, rhs); \
			memoryBuffer.appendWithoutChecking(buffer, \
				Yuni::Core::Traits::Length<typename MemBufT::Type*, typename MemBufT::Size>::Value(buffer)); \
		} \
	}

# define YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL_INT(TYPE) \
	template<class MemBufT> \
	struct Append<MemBufT, TYPE> \
	{ \
		static void Do(MemBufT& memoryBuffer, const TYPE rhs) \
		{ \
			Private::IStringImpl::From<Math::Base::Decimal, TYPE>::AppendTo(memoryBuffer, rhs); \
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

	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(24, "%lf",  float);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(24, "%lf",  double);





} // namespace IStringImpl
} // namespace Private
} // namespace Yuni


#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
