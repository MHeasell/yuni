#ifndef __YUNI_CORE_COLOR_FWD_H__
# define __YUNI_CORE_COLOR_FWD_H__

# include "../math.h"
# include "../string.h"
# include "../static/if.h"
# include "../static/types.h"


namespace Yuni
{
namespace Color
{

	// forward declarations
	template<class T> class RGB;
	template<class T> class RGBA;


} // namespace Color
} // namespace Yuni


namespace Yuni
{
namespace Private
{
namespace Color
{

	/*!
	** \brief A default transparency upperBound, according to a given type
	*/
	template<class T> struct DefaultValues       { enum { lowerBound = 0, upperBound = 255 }; };

	template<> struct DefaultValues<float>       { enum { lowerBound = 0, upperBound = 1 }; };
	template<> struct DefaultValues<double>      { enum { lowerBound = 0, upperBound = 1 }; };
	# ifdef YUNI_HAS_LONG_DOUBLE
	template<> struct DefaultValues<long double> { enum { lowerBound = 0, upperBound = 1 }; };
	# endif


	/*!
	** \brief The most appropriate type for printing
	*/
	template<class T> struct Print  { typedef T Type; };
	template<> struct Print<char>  { typedef int Type; };
	template<> struct Print<unsigned char>  { typedef unsigned int Type; };


	template<class T>
	struct SignedType
	{
		typedef typename Static::If<(T(-1) < T(0)), int, unsigned int>::Type Type;
	};

	template<> struct SignedType<float>       { typedef float Type; };
	template<> struct SignedType<double>      { typedef double Type; };
	# ifdef YUNI_HAS_LONG_DOUBLE
	template<> struct SignedType<long double> { typedef long double Type; };
	# endif

	/*!
	** \brief The most appropriate type for calculation
	*/
	template<class T, class V> struct Calculation
	{
		typedef
			typename Static::If<Static::Type::StrictlyEqual<T, long double>::Yes || Static::Type::StrictlyEqual<V, long double>::Yes,
				long double,
				typename Static::If<Static::Type::StrictlyEqual<T, double>::Yes || Static::Type::StrictlyEqual<V, double>::Yes,
					double,
					typename Static::If<Static::Type::StrictlyEqual<T, float>::Yes || Static::Type::StrictlyEqual<V, float>::Yes,
						float,
						typename SignedType<T>::Type >::Type
				>::Type
			>::Type Type;

	}; // struct Calculation



} // namespace Color
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_COLOR_FWD_H__
