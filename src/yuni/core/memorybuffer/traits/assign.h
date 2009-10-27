#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__


namespace Yuni
{
namespace Private
{
namespace MemoryBufferImpl
{

	template<class MemBufT, class C>
	struct Assign
	{
		static void Do(MemBufT& memoryBuffer, const C& rhs)
		{
			// By Default, we will clear the buffer and then append the new content
			// Which is the standard behavior but may not the most efficient way
			memoryBuffer.clear();
			Append<MemBufT, C>::Do(memoryBuffer, rhs);
		}
	};



	// std::string
	template<class MemBufT, class TraitsT, class AllocT>
	struct Assign<MemBufT, std::basic_string<typename MemBufT::Type, TraitsT,AllocT> >
	{
		typedef std::basic_string<typename MemBufT::Type, TraitsT,AllocT> S;
		static void Do(MemBufT& memoryBuffer, const S& rhs)
		{
			if (!rhs.empty())
				memoryBuffer.assignWithoutChecking(rhs.c_str(), rhs.size());
			else
				memoryBuffer.clear();
		}
	};


	// Yuni::String
	template<class MemBufT, int ChunkSizeT>
	struct Assign<MemBufT, StringBase<typename MemBufT::Type, ChunkSizeT> >
	{
		typedef StringBase<typename MemBufT::Type, ChunkSizeT> S;
		static void Do(MemBufT& memoryBuffer, const S& rhs)
		{
			if (rhs.notEmpty())
				memoryBuffer.assignWithoutChecking(rhs.c_str(), rhs.size());
			else
				rhs.clear();
		}
	};


	// C*
	template<class MemBufT>
	struct Assign<MemBufT, typename MemBufT::Type*>
	{
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C* rhs)
		{
			if (rhs)
				memoryBuffer.assignWithoutChecking(rhs, Core::Traits::Length<C*, typename MemBufT::Size>(rhs));
			else
				memoryBuffer.clear();
		}
	};


	// C[N]
	template<class MemBufT, int N>
	struct Assign<MemBufT, typename MemBufT::Type[N]>
	{
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C rhs[N])
		{
			// The calculation with `N` is required to properly handle
			// both a zero-terminated buffer and a simple array
			memoryBuffer.assignWithoutChecking(rhs, N - ((rhs[N-1] == C()) ? 1 : 0));
		}
	};


	// C
	template<class MemBufT>
	struct Assign<MemBufT, typename MemBufT::Type>
	{
		typedef typename MemBufT::Type C;
		static void Do(MemBufT& memoryBuffer, const C rhs)
		{
			memoryBuffer.assignWithoutChecking(rhs);
		}
	};


	// Core::MemoryBuffer
	template<class MemBufT, unsigned int ChunkSizeT, bool ZeroT, bool ExpandT>
	struct Assign<MemBufT, Core::MemoryBuffer<typename MemBufT::Type, ChunkSizeT, ZeroT, ExpandT> >
	{
		typedef Core::MemoryBuffer<typename MemBufT::Type, ChunkSizeT, ZeroT, ExpandT> C;
		static void Do(MemBufT& memoryBuffer, const C& rhs)
		{
			if (rhs.notEmpty())
				memoryBuffer.assignWithoutChecking(rhs.data(), rhs.size());
			else
				memoryBuffer.clear();
		}
	};


	// nullptr
	template<class MemBufT>
	struct Assign<MemBufT, Yuni::NullPtr>
	{
		static void Do(MemBufT& memoryBuffer, const Yuni::NullPtr&)
		{
			memoryBuffer.clear();
		}
	};



	// bool
	template<class MemBufT>
	struct Assign<MemBufT, bool>
	{
		static void Do(MemBufT& memoryBuffer, const bool rhs)
		{
			if (rhs)
				memoryBuffer.assignWithoutChecking("true", 4);
			else
				memoryBuffer.assignWithoutChecking("false", 5);
		}
	};


# define YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(BUFSIZE, FORMAT, TYPE) \
	template<class MemBufT> \
	struct Assign<MemBufT, TYPE> \
	{ \
		static void Do(MemBufT& memoryBuffer, const TYPE rhs) \
		{ \
			typename MemBufT::Type buffer[BUFSIZE]; \
			(void) YUNI_PRIVATE_MEMBUF_SPTRINF(buffer, BUFSIZE, FORMAT, rhs); \
			memoryBuffer.assignWithoutChecking(buffer, \
				Core::Traits::Length<typename MemBufT::Type*, typename MemBufT::Size>::Value(buffer)); \
		} \
	}


	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL( 8, "%i",   sint16);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(16, "%i",   sint32);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(24, "%lld", sint64);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL( 8, "%u",   uint16);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(16, "%u",   uint32);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(26, "%lld", uint64);

	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(24, "%lf", float);
	YUNI_PRIVATE_MEMORY_BUFFER_ASSIGN_IMPL(24, "%lf", double);




} // namespace MemoryBufferImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_ASSIGN_H__
