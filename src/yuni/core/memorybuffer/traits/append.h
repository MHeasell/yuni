#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__

# include "../../traits/length.h"

# ifdef YUNI_OS_MSVC
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::sprintf_s(BUFFER,SIZE,F,V)
# else
#	define YUNI_PRIVATE_MEMBUF_SPTRINF(BUFFER,SIZE, F, V)  ::sprintf(BUFFER,F,V)
# endif



namespace Yuni
{
namespace Private
{
namespace MemoryBufferImpl
{

	template<class MemBufT, class C>
	struct Append
	{
		// Unknown type
		YUNI_STATIC_ASSERT(false, MemoryBuffer_AppendUnknownType);
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
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C* rhs)
		{
			if (rhs)
				memoryBuffer.appendWithoutChecking(rhs, Yuni::Core::Traits::Length<C*,typename MemBufT::Size>(rhs));
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


	// MemoryBuffer
	template<class MemBufT, unsigned int ChunkSizeT, bool ZeroT, bool ExpandT>
	struct Append<MemBufT, Yuni::MemoryBuffer<typename MemBufT::Type, ChunkSizeT, ZeroT, ExpandT> >
	{
		typedef Yuni::MemoryBuffer<typename MemBufT::Type, ChunkSizeT, ZeroT, ExpandT> C;
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


	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL( 8, "%i",   sint16);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(16, "%i",   sint32);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(24, "%lld", sint64);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL( 8, "%u",   uint16);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(16, "%u",   uint32);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(26, "%lld", uint64);

	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(24, "%lf", float);
	YUNI_PRIVATE_MEMORY_BUFFER_APPEND_IMPL(24, "%lf", double);




} // namespace MemoryBufferImpl
} // namespace Private
} // namespace Yuni


#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_APPEND_H__
