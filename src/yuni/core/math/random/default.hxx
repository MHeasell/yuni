#ifndef __YUNI_CORE_MATH_RANDOM_DEFAULT_HXX__
# define __YUNI_CORE_MATH_RANDOM_DEFAULT_HXX__


namespace Yuni
{
namespace Math
{
namespace Random
{



	inline Default::Value Default::next()
	{
		return ::rand();
	}

	inline Default::Value Default::min()
	{
		return 0;
	}

	inline Default::Value Default::max()
	{
		return RAND_MAX;
	}



	template<class U>
	inline Default& Default::operator >> (U& u)
	{
		u = next();
		return *this;
	}





} // namespace Random
} // namespace Math
} // namespace Yuni

#endif // __YUNI_CORE_MATH_RANDOM_DEFAULT_HXX__
