#ifndef __YUNI_CORE_MATH_GEOMETRY_QUATERNION_HXX__
# define __YUNI_CORE_MATH_GEOMETRY_QUATERNION_HXX__

# include "../math.h"

namespace Yuni
{


	template<class T>
	inline T Quaternion<T>::Magnitude(const Quaternion& q)
	{
		return Math::SquareRoot(q.w * q.w + q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z);
	}


	template<class T>
	template<class U, class V>
	inline void Quaternion<T>::Add(Quaternion<T>& result, const Quaternion<U>& left,
		const Quaternion<V>& right)
	{
		result.w = static_cast<T>(left.w + right.w);
		result.v.x = static_cast<T>(left.v.x + right.v.x);
		result.v.y = static_cast<T>(left.v.y + right.v.y);
		result.v.z = static_cast<T>(left.v.z + right.v.z);
	}


	template<class T>
	template<class U, class V>
	inline void Quaternion<T>::Multiply(Quaternion<T>& result, const Quaternion<U>& left,
		const Quaternion<V>& right)
	{
		result.w = static_cast<T>(left.w * right.w) - Vector3D<T>::DotProduct(left.v, right.v);
		result.v = Vector3D<T>::CrossProduct(left.v, right.v);
		result.v += right.v * left.w + left.v * right.w;
	}

	template<class T>
	template<class U, class V>
	inline Vector3D<U> Quaternion<T>::Rotate(const Vector3D<U>& v, const Vector3D<V>& axis, float angle)
	{
		// The view quaternion is [0, v]
		Quaternion<T> view(0, v);
		float sinA = Math::Sin(angle / 2);
		Quaternion<U> rotation(Math::Cos(angle / 2), axis.x * sinA, axis.y * sinA, axis.z * sinA);
		Quaternion<U> result(Multiply(Multiply(rotation, view), rotation.conjugate()));
		return Vector3D<U>(result.x, result.y, result.z);
	}



	template<class T>
	inline Quaternion<T>::Quaternion():
		w(T()),
		v()
	{}


	template<class T>
	inline Quaternion<T>::Quaternion(T newW, T x, T y, T z):
		w(newW),
		v(x, y, z)
	{}


	template<class T>
	inline Quaternion<T>::Quaternion(T newW, const Vector3D<T>& newV):
		w(newW),
		v(newV)
	{}


	template<class T>
	template<class U>
	inline Quaternion<T>::Quaternion(const Quaternion<U>& other):
		w((T)other.w),
		v(other.v)
	{}


	template<class T>
	inline Quaternion<T>& Quaternion<T>::reset()
	{
		w = T();
		v.reset();
		return *this;
	}


	template<class T>
	inline T Quaternion<T>::magnitude() const
	{
		return Magnitude(*this);
	}


	template<class T>
	inline bool Quaternion<T>::isUnit() const
	{
		return Math::Zero(SquareMagnitude(*this) - 1.0f);
	}


	template<class T>
	inline Quaternion<T> Quaternion<T>::conjugate() const
	{
		return Quaternion<T>();
	}


	template<class T>
	template<class U>
	inline Quaternion<T>& Quaternion<T>::operator = (const Quaternion<U>& other)
	{
		w = static_cast<T>(other.w);
		v = other.v;
	}


	template<class T>
	template<class U>
	inline Quaternion<T>& Quaternion<T>::operator += (const Quaternion<U>& other)
	{
		w += static_cast<T>(other.w);
		v.x += static_cast<T>(other.v.x);
		v.y += static_cast<T>(other.v.y);
		v.z += static_cast<T>(other.v.z);
		return *this;
	}


	template<class T>
	template<class U>
	inline Quaternion<T>& Quaternion<T>::operator *= (const Quaternion<U>& other)
	{
		w = static_cast<T>(w * other.w) - Vector3D<T>::DotProduct(v, other.v);
		Vector3D<T> tmp = Vector3D<T>::CrossProduct(v, other.v);
		tmp += other.v * w + v * other.w;
		v = tmp;
		return *this;
	}


	template<class T>
	inline std::ostream& Quaternion<T>::print(std::ostream& out) const
	{
		out << '[' << w << ", (" << v.x << ',' << v.y << ',' << v.z << ")]";
		return out;
	}



} // namespace Yuni

#endif // __YUNI_CORE_MATH_GEOMETRY_QUATERNION_HXX__

