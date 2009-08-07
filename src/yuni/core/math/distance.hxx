#ifndef __YUNI_CORE_MATH_DISTANCE_HXX__
# define __YUNI_CORE_MATH_DISTANCE_HXX__

# include "../static/types.h"


namespace Yuni
{
namespace Private
{
namespace MathImpl
{

	template<typename T, bool IsDecimal>
	struct Distance2D
	{
		static inline T Compute(T x1, T y1, T x2, T y2)
		{
			return SquareRoot<T>((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		}
	};

	template<typename T>
	struct Distance2D<T,0>
	{
		static inline T Compute(T x1, T y1, T x2, T y2)
		{
			return RoundToType<double,T>::Value(
				SquareRoot<double>(
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
		}
	};


	template<typename T, bool IsDecimal>
	struct Distance3D
	{
		static inline T Compute(T x1, T y1, T x2, T y2)
		{
			return SquareRoot<T>((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
		}
	};

	template<typename T>
	struct Distance3D<T,0>
	{
		static inline T Compute(T x1, T y1, T x2, T y2)
		{
			return RoundToType<double,T>::Value(
				SquareRoot<double>(
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1))));
		}
	};


} // namespace MathImpl
} // namespace Private
} // namespace Yuni

namespace Yuni
{
namespace Math
{


	template<typename T> inline T Distance2D(T x1, T y1, T x2, T y2)
	{
		return Private::MathImpl::Distance2D<T,Static::Type::IsDecimal<T>::Yes>
			(x1, y1, x2, y2);
	}

	template<typename T> inline T Distance3D(T x1, T y1, T z1, T x2, T y2, T z2)
	{
		return Private::MathImpl::Distance3D<T,Static::Type::IsDecimal<T>::Yes>
			(x1, y1, z1, x2, y2, z2);
	}



} // namespace Math
} // namespace Yuni

#endif // __YUNI_CORE_MATH_DISTANCE_H__
