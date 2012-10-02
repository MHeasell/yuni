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
	template<class U>
	inline Vector3D<T> Quaternion<T>::Rotate(const Vector3D<T>& v, const Vector3D<U>& axis, T angle)
	{
		// The view quaternion is [0, v]
		Quaternion<T> view(0, v);
		T sinA = Math::Sin(angle / (T)2);
		Quaternion<T> rot(Math::Cos(angle / (T)2), axis.x * sinA, axis.y * sinA, axis.z * sinA);
		return ((rot * view) * rot.conjugate()).v;
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
	inline Quaternion<T>& Quaternion<T>::clear()
	{
		w = T();
		v.clear();
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
		return Math::Zero(SquareMagnitude(*this) - T(1));
	}


	template<class T>
	inline Quaternion<T> Quaternion<T>::conjugate() const
	{
		return Quaternion<T>(w, -v.x, -v.y, -v.z);
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

