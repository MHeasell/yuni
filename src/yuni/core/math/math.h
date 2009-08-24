#ifndef __YUNI_CORE_MATH_MATH_H__
# define __YUNI_CORE_MATH_MATH_H__

# include "../../yuni.h"
# include <stdlib.h>
# include <math.h>


/*!
** \brief An Arbitrarily (or nearly so) small positive quantity
** \ingroup Math
*/
# define YUNI_EPSILON  1.e-6

/*!
** \brief Pi, A Mathematical constant (π)
**
** Pi is a mathematical constant whose value is the ratio of any circle's
** circumference to its diameter in Euclidean space.
** \see http://en.wikipedia.org/wiki/Pi
** \ingroup Math
*/
# define YUNI_PI               3.14159265358979323846

//! The reciprocal value of PI
# define YUNI_RECIPROCAL_PI    1. / YUNI_PI

//! The half value of PI
# define YUNI_HALF_PI          YUNI_PI / 2.

/*!
** \brief E, A Mathematical constant
**
** The mathematical constant e is the unique real number such that the area
** above the x-axis and below the curve y=1/x for 1 ≤ x ≤ e is exactly 1.
** \see http://en.wikipedia.org/wiki/E_(mathematical_constant)
** \ingroup Math
*/
# define YUNI_NAT_E   2.71828182845904523536




namespace Yuni
{

/*!
** \brief Common mathematical operations, transformations and constants
** \ingroup Math
*/
namespace Math
{


	/*!
	** \brief Get if two values are equal
	** \ingroup Math
	*/
	template<typename U> bool Equals(U a, U b);

	/*!
	** \brief Get if a value is equals to zero
	*/
	template<typename U> bool Zero(U a);


	/*!
	** \brief Get the integer absolute value
	** \ingroup Math
	*/
	inline int Abs(const int a)  {return abs(a);}
	inline float Abs(const float a)  {return fabsf(a);}
	inline double Abs(const double a)  {return fabs(a);}
	inline long double Abs(const long double a)  {return fabsl(a);}

	/*!
	** \brief Get the greater expression
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the grater
	*/
	template<typename U, typename V> inline U Max(U a, V b);

	/*!
	** \brief Maximum of three values
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \param c The third expression
	** \return The expression considered as the grater
	*/
	template<typename T> inline const T& Max(const T& a, const T& b, const T& c);

	/*!
	** \brief Get the smallest expression
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the smaller
	*/
	template<typename U, typename V> inline U Min(U a, V b);

	/*!
	** \brief Minimum of three values
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \param c The third expression
	** \return The expression considered as the smaller
	*/
	template<typename T> inline const T& Min(const T& a, const T& b, const T& c);


	/*!
	** \brief Ensure that an expression is contained in a range of values
	** \ingroup Math
	**
	** \param expr An expression
	** \param min The lower bound limit allowed for the expression `v`
	** \param max The upper bound limit allowed for the expression `v`
	** \return The expression itself, or a bound limit
	*/
	template<typename T> inline const T& MinMax(const T& expr, const T& min, const T& max);


	/*!
	** \brief Swap two values
	** \ingroup Math
	**
	** \param a The first value
	** \param b the second value
	*/
	template<typename T> inline void Swap(T& a, T&b);



	/*!
	** \brief The factorial function
	** \ingroup Math
	**
	** \code
	**    std::cout << Factorial<7>::value << std::endl;
	** \endcode
	*/
	template <int N>
	struct Factorial
	{
		//! The Formula for the factorial function
		enum { value = N * Factorial<N-1>::value };
		// Fatorial<1> is located in math.hxx

	}; // class Factorial



	/*!
	** \brief Get the value of x raised to the power y (x**y)
	**
	** \param x Any value
	** \param y The power y
	** \return x**y
	** \ingroup Math
	*/
	inline float Power(const float x, const float y);
	inline double Power(const double x, const double y);

	/*!
	** \brief The power function for Integer values
	** \ingroup Math
	**
	** \f$value = x^y\f$
	**
	** \tparam X The value
	** \tparam Y The power
	**
	** \code
	**    std::cout << Yuni::Math::Power<8, 3>::value << std::endl; // 512
	** \endcode
	*/
	template<int X, int Y>
	struct PowerInt
	{
		//! The formula for the power function
		enum { value = X * PowerInt<X, Y-1>::value };
		// PowerInt<X,0> is located in math.hxx

	}; // class Power




	/*!
	** \brief Get the square root value
	** \ingroup Math
	*/
	template<typename U> U SquareRoot(const U x);


	/*!
	** \brief The Square root function for integer values
	** \ingroup Math
	**
	** \f$value = \sqrt{N}\f$
	**
	** \code
	**    std::cout << SquareRoot<16>::value << std::endl; // 4
	** \endcode
	**
	** \internal Via iteration
	*/
	template <int N, int I = 1>
	struct SquareRootInt
	{
		//! The formula for the squere root function
		enum { value = (I*I < N) ? SquareRootInt<N, I+1>::value : I };
		// SquareRootInt<N,N> is located in math.hxx

	}; // class SquareRoot


	/*!
	** \brief Get if a value is a power of 2
	*/
	inline bool PowerOfTwo(const int x);



	/*!
	** \brief Convert degree to radion
	** \note This method is provided for convenience only. You should
	**       see Yuni::Unit for more functionalities.
	*/
	template<typename T> inline T DegreeToRadian(const T x);


	/*!
	** \brief Convert radion to degree
	** \note This method is provided for convenience only. You should
	**       see Yuni::Unit for more functionalities.
	*/
	template<typename T> inline T RadianToDegree(const T x);



	/*!
	** \brief Determine whether the argument value is a NaN
	*/
	template<typename T> inline bool NaN(const T& x);


	/*!
	** \brief Floor function
	*/
	template<typename T> inline T Floor(T x);

	/*!
	** \brief Ceil function
	*/
	template<typename T> inline T Ceil(T x);


	/*!
	** \brief The fractional part function
	*/
	template<typename T> inline T Fract(T x);


	/*!
	** \brief Integral value nearest to x
	**
	** The function returns the integral value nearest to x rounding
	** half-way cases away from zero, regardless of the current rounding
	** direction.
	*/
	template<typename T> inline T Round(T x);


	/*!
	** \brief Integral value nearest to x
	**
	** Here is the best way to use this class :
	** \code
	** int i = RoundToInt<float,int>::Value(10.2f);
	** \endcode
	*/
	template<typename T, typename R> struct RoundToInt;



} // namespace Math
} // namespace Yuni

# include "math.hxx"

#endif // __YUNI_CORE_MATH_MATH_H__
