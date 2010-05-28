#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__

# include "../../traits/length.h"

namespace Yuni
{
namespace Extension
{
namespace CustomString
{


	template<class CustomStringT, class U>
	struct Fill
	{
		// Unknown type
	};

	template<class CustomStringT>
	struct Fill<CustomStringT, char>
	{
		typedef char S;
		static void Perform(typename CustomStringT::Type* data, typename CustomStringT::Size size, const S rhs)
		{
			(void)::memset(data, rhs, size);
		}
	};

	template<class CustomStringT>
	struct Fill<CustomStringT, wchar_t>
	{
		typedef wchar_t S;
		static void Perform(typename CustomStringT::Type* data, typename CustomStringT::Size size, const S rhs)
		{
			(void)::wmemset(data, rhs, size);
		}
	};


	template<class CustomStringT>
	struct Fill<CustomStringT, typename CustomStringT::Type*>
	{
		typedef typename CustomStringT::Type C;
		static void Perform(typename CustomStringT::Type* data, typename CustomStringT::Size size, const C* pattern)
		{
			// Alias for the size type
			typedef typename CustomStringT::Size Size;

			// Getting the size of the pattern
			const Size patternSize = Yuni::Traits::Length<C*,Size>::Value(pattern);
			// If equals to 1, it is merely a single char
			if (patternSize == 1)
			{
				Fill<CustomStringT, typename CustomStringT::Type>::Perform(data, size, *pattern);
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





} // namespace CustomString
} // namespace Extension
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_FILL_H__
