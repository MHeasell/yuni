#ifndef __YUNI_CORE_MATH_GEOMETRY_VECTOR3D_HXX__
# define __YUNI_CORE_MATH_GEOMETRY_VECTOR3D_HXX__


namespace Yuni
{
namespace Gfx
{


	template<typename T>
	inline Vector3D<T>
	Vector3D<T>::Mean(const Vector3D<T>& p1, const Vector3D<T>& p2)
	{
		return Vector3D<T>().mean(p1, p2);
	}


	template<typename T>
	inline Vector3D<T>::Vector3D()
		:x(), y(), z()
	{}

	template<typename T>
	inline Vector3D<T>::Vector3D(const Vector3D<T>& rhs)
		:x(rhs.x), y(rhs.y), z(rhs.z)
	{}


	template<typename T>
	template<typename U>
	inline Vector3D<T>::Vector3D(const Vector3D<U>& rhs)
		:x((T)rhs.x), y((T)rhs.y), z((T)rhs.z)
	{}


	template<typename T>
	template<typename U, typename V, typename W>
	inline Vector3D<T>::Vector3D(const U x1, const V y1, const W z1)
		:x((T)x1), y((T)y1), z((T)z1)
	{}

	template<typename T>
	template<typename U, typename V>
	inline Vector3D<T>::Vector3D(const Point3D<U>& origin, const Point3D<V>& end)
		:x((T)(end.x - origin.x)), y((T)(end.y - origin.y)), z((T)(end.z - origin.z))
	{}

	template<typename T>
	inline Vector3D<T>& Vector3D<T>::reset()
	{
		x = y = z = T();
		return *this;
	}


	template<typename T>
	template<typename U>
	inline void Vector3D<T>::translate(const U v)
	{
		x += (T)v;
		y += (T)v;
		z += (T)v;
	}


	template<typename T>
	template<typename U, typename V, typename W>
	inline void Vector3D<T>::translate(const U x1, const V y1, const W z1)
	{
		x += (T)x1;
		y += (T)y1;
		z += (T)z1;
	}

	template<typename T>
	template<typename U>
	inline void Vector3D<T>::translate(const Vector3D<U>& v)
	{
		x += (T)v.x;
		y += (T)v.y;
		z += (T)v.z;
	}


	template<typename T>
	template<typename U>
	inline Vector3D<T>& Vector3D<T>::mean(const Vector3D<U>& p)
	{
		x = (T) ((x + (T)p.x) / 2.);
		y = (T) ((y + (T)p.y) / 2.);
		z = (T) ((z + (T)p.z) / 2.);
		return *this;
	}


	template<typename T>
	template<typename U, typename V>
	inline Vector3D<T>& Vector3D<T>::mean(const Vector3D<U>& p1, const Vector3D<V>& p2)
	{
		x = (T) ((p1.x + p2.x) / 2.0f);
		y = (T) ((p1.y + p2.y) / 2.0f);
		z = (T) ((p1.z + p2.z) / 2.0f);
		return *this;
	}



	template<typename T>
	template<typename U, typename V, typename W>
	inline void Vector3D<T>::operator () (const U x1, const V y1, const W z1)
	{
		x = (T)x1;
		y = (T)y1;
		z = (T)z1;
	}


	template<typename T>
	template<typename U>
	inline void Vector3D<T>::operator () (const Vector3D<U>& v)
	{
		x = (T)v.x;
		y = (T)v.y;
		z = (T)v.z;
	}


	template<typename T>
	inline std::ostream& Vector3D<T>::print(std::ostream& out) const
	{
		out << x << "," << y << "," << z;
		return out;
	}


	template<typename T>
	inline bool Vector3D<T>::null() const
	{
		return Math::Zero(x) && Math::Zero(y) && Math::Zero(z);
	}


	template<typename T>
	Vector3D<T>& Vector3D<T>::normalize()
	{
		T m = magnitude();
		if (!Math::Zero(m))
		{
			x /= m;
			y /= m;
			z /= m;
		}
		return *this;
	}

	template<typename T>
	Vector3D<T>& Vector3D<T>::normalize(const T coeff)
	{
		T m = magnitude();
		if (!Math::Zero(m))
		{
			m = coeff / m;
			x *= m;
			y *= m;
			z *= m;
		}
		return *this;
	}




	template<typename T>
	inline T Vector3D<T>::magnitude() const
	{
		return Math::SquareRoot(x*x + y*y + z*z);
	}

	template<typename T>
	inline T Vector3D<T>::Magnitude(const Vector3D& p1, const Vector3D& p2)
	{
		return Math::SquareRoot(p1.x*p2.x + p1.y*p2.y + p1.z*p2.z /* dot product */);
	}

	template<typename T>
	inline T Vector3D<T>::dotProduct(const Vector3D& p1) const
	{
		return p1.x*x + p1.y*y + p1.z*z;
	}

	template<typename T>
	inline T Vector3D<T>::DotProduct(const Vector3D& p1, const Vector3D& p2)
	{
		return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
	}

	template<typename T>
	inline Vector3D<T> Vector3D<T>::CrossProduct(const Vector3D<T>& p1, const Vector3D<T>& p2)
	{
		return Vector3D
			(p1.y * p2.z - p1.z * p2.y,
			p1.z * p2.x - p1.x * p2.z,
			p1.x * p2.y - p1.y * p2.x);
	}





	template<typename T>
	inline Vector3D<T>& Vector3D<T>::operator += (const T k)
	{
		x += k;
		y += k;
		z += k;
		return (*this);
	}

	template<typename T>
	template<typename U>
	inline Vector3D<T>& Vector3D<T>::operator += (const Vector3D<U>& p)
	{
		x += (T)p.x;
		y += (T)p.y;
		z += (T)p.z;
		return (*this);
	}

	template<typename T>
	inline Vector3D<T>& Vector3D<T>::operator -= (const T k)
	{
		x -= k;
		y -= k;
		z -= k;
		return (*this);
	}

	template<typename T>
	template<typename U>
	inline Vector3D<T>& Vector3D<T>::operator -= (const Vector3D<U>& p)
	{
		x -= (T)p.x;
		y -= (T)p.y;
		z -= (T)p.z;
		return (*this);
	}


	template<typename T>
	inline Vector3D<T>& Vector3D<T>::operator *= (const T k)
	{
		x *= k;
		y *= k;
		z *= k;
		return (*this);
	}

	template<typename T>
	inline Vector3D<T>& Vector3D<T>::operator /= (const T k)
	{
		if (!Math::Zero(k))
		{
			x /= k;
			y /= k;
			z /= k;
		}
		return (*this);
	}


	template<typename T>
	template<typename U>
	inline Vector3D<T>& Vector3D<T>::operator *= (const Vector3D<U>& p)
	{
		x -= (T)p.x;
		y -= (T)p.y;
		z -= (T)p.z;
		return (*this);
	}

	template<typename T>
	template<typename U>
	inline Vector3D<T>& Vector3D<T>::operator /= (const Vector3D<U>& p)
	{
		x -= (T)p.x;
		y -= (T)p.y;
		z -= (T)p.z;
		return (*this);
	}



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_CORE_MATH_GEOMETRY_VECTOR3D_HXX__
