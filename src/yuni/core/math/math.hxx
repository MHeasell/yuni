#ifndef __YUNI_CORE_MATH_MATH_HXX__
# define __YUNI_CORE_MATH_MATH_HXX__

# include <algorithm>


namespace Yuni
{
namespace Math
{


	template<typename U, typename V>
	inline U Max(U a, V b)
	{
		return (a < b) ? b : a;
	}


	template<typename T>
	inline const T& Max(const T& a, const T& b, const T& c)
	{
		return Max<T,T>(Max<T,T>(a, b), c);
	}


	template<typename U, typename V>
	inline U Min(U a, V b)
	{
		return (a < b) ? a : b;
	}



	template<typename T>
	inline const T& Min(const T& a, const T& b, const T& c)
	{
		return Min<T>(Min<T>(a, b), c);
	}


	template<typename T>
	inline void Swap(T& a, T&b)
	{
		std::swap(a, b);
	}


	template<typename T>
	inline const T& MinMax(const T& expr, const T& min, const T& max)
	{
		return ((expr < min)
				? min : ((expr > max)
					? max : expr));
	}



	//! Factorial(1) = 1
	template <> struct Factorial<1> { enum { value = 1 }; };


	//! PowerInt<X,0>
	template <int X> struct PowerInt<X,0> { enum { value = 1 }; };

	// partial specialization to end the iteration
	template<int N> struct SquareRootInt<N,N> { enum { value = N }; };


	template <typename U> inline bool Equals(U a, U b)
	{
		return (a == b);
	}


	template<> inline bool Equals<float>(float a, float b)
	{
		return ::fabsf(a - b) < YUNI_EPSILON;
	}

	template<> inline bool Equals<double>(double a, double b)
	{
		return ::fabs(a - b) < YUNI_EPSILON;
	}

	template<> inline bool Equals<long double>(long double a, long double b)
	{
		return ::fabsl(a - b) < YUNI_EPSILON;
	}



	template <typename U> inline bool Zero(U a)
	{
		return (0 == a);
	}

	template<> inline bool Zero<float>(float a)
	{
		return ::fabsf(a) < YUNI_EPSILON;
	}

	template<> inline bool Zero<double>(double a)
	{
		return ::fabs(a) < YUNI_EPSILON;
	}

	template<> inline bool Zero<long double>(long double a)
	{
		return ::fabsl(a) < YUNI_EPSILON;
	}



	inline float SquareRoot(const float x)
	{
		return ::sqrtf(x);
	}

	inline double SquareRoot(const double x)
	{
		return ::sqrt(x);
	}




	inline bool PowerOfTwo(const int x)
	{
		return !(x & (x - 1)) && x;
	}


	template<typename T> inline T DegreeToRadian(const T x)
	{
		return (x * 0.017453292);
	}


	template<typename T> inline T RadianToDegree(const T x)
	{
		return (x * 57.29578122);
	}


	template<typename T> inline bool NaN(const T& x)
	{
		return (isnan(x));
	}



	template<typename T> inline T Floor(T x)
	{
		return x;
	}

	template<> inline float Floor(float x)
	{
		return ::floorf(x);
	}

	template<> inline double Floor(double x)
	{
		return ::floor(x);
	}

	template<> inline long double Floor<long double>(long double x)
	{
		return ::floorl(x);
	}



	template<typename T> inline T Ceil(T x)
	{
		return x;
	}

	template<> inline float Ceil(float x)
	{
		return ::ceilf(x);
	}

	template<> inline double Ceil(double x)
	{
		return ::ceil(x);
	}

	template<> inline long double Ceil<long double>(long double x)
	{
		return ::ceill(x);
	}



	template<typename T> inline T Fract(T x)
	{
		return x - Floor(x);
	}



	inline float FastInvSquareRoot(float x)
	{
		float xhalf = 0.5f * x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(float*)&i;
		return x * (1.5f - xhalf * x * x);
	}


	
	inline float Power(const float x, const float y)
	{
		return ::powf(x, y);
	}

	inline double Power(const double x, const double y) 
	{
		return ::pow(x, y);
	}


} // namespace Math
} // namespace Yuni


#endif // __YUNI_CORE_MATH_MATH_HXX__
