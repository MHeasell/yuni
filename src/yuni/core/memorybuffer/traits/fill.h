#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__

# include "../../traits/length.h"

namespace Yuni
{
namespace Private
{
namespace IStringImpl
{

	template<class MemBufT, class U>
	struct Fill
	{
		// Unknown type
	};

	template<class MemBufT>
	struct Fill<MemBufT, char>
	{
		typedef char S;
		static void Do(typename MemBufT::Type* data, typename MemBufT::Size size, const S rhs)
		{
			(void)::memset(data, rhs, size);
		}
	};

	template<class MemBufT>
	struct Fill<MemBufT, wchar_t>
	{
		typedef wchar_t S;
		static void Do(typename MemBufT::Type* data, typename MemBufT::Size size, const S rhs)
		{
			(void)::wmemset(data, rhs, size);
		}
	};


	template<class MemBufT>
	struct Fill<MemBufT, typename MemBufT::Type*>
	{
		typedef typename MemBufT::Type C;
		static void Do(typename MemBufT::Type* data, typename MemBufT::Size size, const C* pattern)
		{
			// Alias for the size type
			typedef typename MemBufT::Size Size;

			// Getting the size of the pattern
			const Size patternSize = Yuni::Core::Traits::Length<C*,Size>::Value(pattern);
			// If equals to 1, it is merely a single char
			if (patternSize == 1)
			{
				Fill<MemBufT, typename MemBufT::Type>::Do(data, size, *pattern);
				return;
			}
			// We have to copy N times the pattern
			Size p(0);
			while (p + patternSize <= size)
			{
				(void)::memcpy(data + p, pattern, patternSize * sizeof(C));
				p += patternSize;
			}
		}
	};





} // namespace IStringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__
