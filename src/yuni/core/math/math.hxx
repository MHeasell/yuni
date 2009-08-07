#ifndef __YUNI_CORE_MATH_MATH_HXX__
# define __YUNI_CORE_MATH_MATH_HXX__

# include <algorithm>


#ifdef YUNI_OS_WINDOWS
/* Those functions are not available on Windows... */
double rint(double nr);
long double rintl(long double x);
float rintf(float x);
long int lrint(double x);
long int lrintl(long double x);
long int lrintf(float x);
long long int llrint(double x);
long long int llrintl(long double x);
long long int llrintf(float x);
#endif



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

	template<> inline float Ceil(const float x)
	{
		return ::ceilf(x);
	}

	template<> inline double Ceil(const double x)
	{
		return ::ceil(x);
	}

	template<> inline long double Ceil<long double>(const long double x)
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


	template<typename T> inline T Round(T x)
	{
		return x;
	}


	template<> inline double Round<double>(double x)
	{
		# ifdef YUNI_OS_MSVC
		return ::floor(x + 0.5);
		# else
		return ::round(x);
		# endif
	}

	template<> inline long double Round<long double>(long double x)
	{
		# ifdef YUNI_OS_MSVC
		return ::floorl(x + 0.5L);
		# else
		return ::roundl(x);
		# endif
	}

	template<> inline float Round<float>(float x)
	{
		# ifdef YUNI_OS_MSVC
		return ::floorf(x + 0.5f);
		# else
		return ::roundf(x);
		# endif
	}


	template<typename T, typename R>
	struct RoundToInt
	{
		typedef T Type;
		typedef R ResultType;
		static inline ResultType Value(Type x)
		{
			// Default Behavior
			return (ResultType)(Round<Type>(x));
		}
	};

	template<typename T>
	struct RoundToInt<T,T>
	{
		typedef T Type;
		typedef T ResultType;
		static inline ResultType Value(Type x)
		{
			// Same type nothing to do
			return x;
		}
	};


	template<>
	struct RoundToInt<float, long int>
	{
		typedef float Type;
		typedef long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::lrintf(x);
		}
	};

	template<>
	struct RoundToInt<double, long int>
	{
		typedef double Type;
		typedef long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::lrint(x);
		}
	};

	template<>
	struct RoundToInt<long double, long int>
	{
		typedef long double Type;
		typedef long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::lrintl(x);
		}
	};



	template<>
	struct RoundToInt<float, long long int>
	{
		typedef float Type;
		typedef long long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::llrintf(x);
		}
	};

	template<>
	struct RoundToInt<double, long long int>
	{
		typedef double Type;
		typedef long long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::llrint(x);
		}
	};

	template<>
	struct RoundToInt<long double, long long int>
	{
		typedef long double Type;
		typedef long long int ResultType;
		static inline ResultType Value(Type x)
		{
			return ::llrintl(x);
		}
	};




} // namespace Math
} // namespace Yuni





#ifdef YUNI_OS_WINDOWS

/* Those functions are not available on Windows... */

inline double rint(double nr)
{
	const double f = Yuni::Math::Floor(nr);
	const double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? f : c);
}

inline long double rintl(long double nr)
{
	const long double f = Yuni::Math::Floor(nr);
	const long double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? f : c);
}

inline float rintf(float nr)
{
	const float f = Yuni::Math::Floor(nr);
	const float c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? f : c);
}

inline long int lrint(double nr)
{
	const double f = Yuni::Math::Floor(nr);
	const double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long int)f : (long int)c);
}

inline long int lrintl(long double nr)
{
	const long double f = Yuni::Math::Floor(nr);
	const long double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long int)f : (long int)c);
}

inline long int lrintf(float nr)
{
	const float f = Yuni::Math::Floor(nr);
	const float c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long int)f : (long int)c);
}

inline long long int llrint(double nr)
{
	const double f = Yuni::Math::Floor(nr);
	const double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long long int)f : (long long int)c);
}

inline long long int llrintl(long double nr)
{
	const long double f = Yuni::Math::Floor(nr);
	const long double c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long long int)f : (long long int)c);
}

inline long long int llrintf(float nr)
{
	const float f = Yuni::Math::Floor(nr);
	const float c = Yuni::Math::Ceil(nr);
	return (((c -nr) >= (nr - f)) ? (long long int)f : (long long int)c);
}

#endif /* ifdef WINDOWS */


#endif // __YUNI_CORE_MATH_MATH_HXX__
