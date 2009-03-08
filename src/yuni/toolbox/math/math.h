#ifndef __YUNI_TOOLBOX_MATH_MATH_H__
# define __YUNI_TOOLBOX_MATH_MATH_H__

# include <stdlib.h>
# include <math.h>
# include <cstring>


# define YUNI_EPSILON 0.00001

namespace Yuni
{

/*!
** \brief Common mathematical operations and transformations
** \ingroup Math
*/
namespace Math
{

	/*!
	** \brief Get the integer absolute value
	** \ingroup Math
	*/
	inline int Abs(const int a)  {return abs(a);}
	inline float Abs(const float a)  {return fabsf(a);}
	inline double Abs(const double a)  {return fabs(a);}

	/*!
	** \brief Get the expression considered as the greater
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the grater
	*/
	template<typename T>
	inline const T& Max(const T& a, const T& b)  {return a < b ? b : a;}

	// Maximum of two C-strings
	inline const char* Max(const char* a, const char* b) {return std::strcmp(a, b) < 0 ? b : a;}

	/*!
	** \brief Maximum of three values
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \param c The third expression
	** \return The expression considered as the grater
	*/
	template<typename T>
	inline const T& Max(const T& a, const T& b, const T& c) {return Max<T>(Max<T>(a, b), c);}

	/*!
	** \brief Get the expression considered as the smaller
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the smaller
	*/
	template<typename T>
	inline const T& Min(const T& a, const T& b)  {return a < b ? a : b;}

	// Minimum of two C-strings
	inline const char* Min(const char* a, const char* b) {return std::strcmp(a, b) < 0 ? a : b;}

	/*!
	** \brief Minimum of three values
	** \ingroup Math
	**
	** \param a The first expression
	** \param b The second expression
	** \param c The third expression
	** \return The expression considered as the smaller
	*/
	template<typename T>
	inline const T& Min(const T& a, const T& b, const T& c) {return Min<T>(Min<T>(a, b), c);}



	/*!
	** \brief Ensure that an expression was contained in a range of values
	** \ingroup Math
	**
	** \param expr An expression
	** \param min The lower bound limit allowed for the expression `v`
	** \param max The upper bound limit allowed for the expression `v`
	** \return The expression itself, or a bound limit
	*/
	template<typename T>
	inline const T& MinMax(const T& expr, const T& min, const T& max)
	{return ((expr < min) ? min : ((expr > max) ? max : expr));}


	/*!
	** \brief Ensure an expression is contained in a range of values
	** \ingroup Math
	**
	** \param[in,out] expr The expression that must be checked and modified if needed
	** \param min The lower bound limit allowed for the expression `v`
	** \param max The upper bound limit allowed for the expression `v`
	** \return Always `expr`
	*/
	template<typename T>
	inline T& EnsureInRange(T& expr, const T& min, const T& max)
	{
		if (expr < min)
			expr = min;
		else
		{
			if (expr > max)
				expr = max;
		}
		return expr;
	}


	/*!
	** \brief Swap the value of two variables
	** \ingroup Math
	**
	** \param a The first value
	** \param b the second value
	*/
	template<typename T>
	inline void Swap(T& a, T&b) { T tmp(b); b = a; a = tmp; }



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
		enum { value = N * Factorial<N-1>::value };
	};

	//! Factorial(1) = 1
	template <> struct Factorial<1> { enum { value = 1 }; };



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
	struct Power
	{
		enum { value = X * Power<X, Y-1>::value };
	}; // class Power

	template <int X> struct Power<X,0> { enum { value = 1 }; };




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
	struct SquareRoot
	{
		enum { value = (I*I < N) ? SquareRoot<N, I+1>::value : I };
	}; // class SquareRoot

	// partial specialization to end the iteration
	template<int N> struct SquareRoot<N,N> { enum { value = N }; };


	/*!
	** \brief Compare two floats
	** \ingroup Math
	*/
	template <typename U>
	inline bool Equals(const U a, const U b) {return (a == b);}

	template<> inline bool Equals(const float a, const float b) {return Abs(a - b) < YUNI_EPSILON;}
	template<> inline bool Equals(const double a, const double b) {return Abs(a - b) < YUNI_EPSILON;}




} // namespace Math
} // namespace Yuni


#endif // __YUNI_TOOLBOX_MATH_MATH_H__
