#ifndef __YUNI_TOOLBOX_MATH_EXPONENTIAL_HXX__
# define __YUNI_TOOLBOX_MATH_EXPONENTIAL_HXX__



namespace Yuni
{
namespace Math
{

	template<typename T> ALWAYS_INLINE inline T Exp(T x)
	{
		return (T)::exp((T)x);
	}

	template<> ALWAYS_INLINE inline float Exp(float x)
	{
		return ::expf(x);
	}

	template<> ALWAYS_INLINE inline double Exp(double x)
	{
		return ::exp(x);
	}

	template<> ALWAYS_INLINE inline long double Exp<long double>(long double x)
	{
		return ::expl(x);
	}





} // namespace Math
} // namespace Yuni

#endif // __YUNI_TOOLBOX_MATH_EXPONENTIAL_HXX__
