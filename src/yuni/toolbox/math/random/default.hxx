#ifndef __YUNI_TOOLBOX_MATH_RANDOM_DEFAULT_HXX__
# define __YUNI_TOOLBOX_MATH_RANDOM_DEFAULT_HXX__


namespace Yuni
{
namespace Math
{
namespace Random
{



	inline void Default::reset()
	{
		srand((unsigned int)time(NULL));
		rand();
	}

	inline void Default::reset(const unsigned int seed)
	{
		srand(seed);
		rand();
	}


	inline const Default::Value Default::next()
	{
		return rand();
	}

	inline const Default::Value Default::min()
	{
		return 0;
	}

	inline const Default::Value Default::max()
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

#endif // __YUNI_TOOLBOX_MATH_RANDOM_DEFAULT_HXX__
