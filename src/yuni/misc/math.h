#ifndef __YUNI_MISC_MATH_H__
# define __YUNI_MISC_MATH_H__

# include <stdlib.h>
# include <math.h>


namespace Yuni
{
namespace Math
{

	/*!
	** \brief Get the integer absolute value
	*/
	inline int Abs(const int a)  {return abs(a);}
	inline float Abs(const float a)  {return fabsf(a);}
	inline double Abs(const double a)  {return fabs(a);}

	/*!
	** \brief Get the expression considered as the greater
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the grater
	*/
	template<typename T>
	inline const T& Max(const T& a, const T& b)  {return a < b ? b : a;}

	/*!
	** \brief Get the expression considered as the smaller
	**
	** \param a The first expression
	** \param b The second expression
	** \return The expression considered as the smaller
	*/
	template<typename T>
	inline const T& Min(const T& a, const T& b)  {return a < b ? a : b;}


	/*!
	** \brief Ensure that an expression was contained in a range of values
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
	**
	** \param a The first value
	** \param b the second value
	*/
	template<typename T>
	inline void Swap(T& a, T&b) { T tmp(b); b = a; a = tmp; }



	/*!
	** \brief The factorial function
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
	** \brief The power function
	**
	** \f$value = x^y\f$
	**
	** \tparam X The value
	** \tparam Y The power
	**
	** \code
	**    std::cout << Power<8, 3>::value << std::endl; // 512
	** \endcode
	*/
	template<int X, int Y>
	struct Power
	{
		enum { value = X * Power<X,Y-1>::value };
	};

	template <int X> struct Power<X,0> { enum { value = 1 }; };




	/*!
	** \brief The Square root function
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
	};

	// partial specialization to end the iteration
	template<int N> struct SquareRoot<N,N> { enum { value = N }; };




} // namespace Math
} // namespace Yuni

#endif // __YUNI_MISC_MATH_H__
