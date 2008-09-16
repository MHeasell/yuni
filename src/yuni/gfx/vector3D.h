#ifndef __YUNI_GFX_VECTOR3D_H__
# define __YUNI_GFX_VECTOR3D_H__

# include <iostream>
# include "../misc/math.h"



namespace Yuni
{
namespace Gfx
{


	/*!
	** \class Vector3D
	** \brief Represents a 3D-vector, with generic homogeneous content
	*/
	template<typename T = float>
	class Vector3D
	{
	public:
		//! \name Constructors
		//@{

		//! Default constructor
		Vector3D() : x(0), y(0), z(0) {}

		/*!
		** \brief Constructor
		** \param x1 The default X coordinate
		** \param y1 The default Y coordinate
		*/
		template<typename U, typename V>
		Vector3D(const U x1, const V y1): x((T)x1), y((T)y1), z(T()) {}

		/*!
		** \brief Constructor
		** \param x1 The default X coordinate
		** \param y1 The default Y coordinate
		** \param z1 The default Z coordinate
		*/
		template<typename U, typename V, typename W>
		Vector3D(const U x1, const V y1, const W z1): x((T)x1), y((T)y1), z((T)z1) {}
		
		//! Constructor by copy
		template<typename U>
		Vector3D(const Vector3D<U>& v) : x((T)v.x), y((T)v.y), z((T)v.z) {}
		
		//@} // Constructors

		//! Reset the vector to the null vector
		Vector3D<T>& reset() {x = y = z = T(); return *this;}

		/*!
		** \brief Add coordinates to a vector
		** 
		** \param x1 The X coordinate to add
		** \param y1 The Y coordinate to add
		** \param z1 The Z coordinate to add
		*/
		template<typename U, typename V, typename W>
		void add(const U x1, const V y1, const W z1) { x += (T)x1; y += (T)y1; z += (T)z1; }
		/*!
		** \brief Add two vectors
		** \param p The new coordinates
		*/
		template<typename U>
		void add(const Vector3D<U>& p) { x += (T)p.x; y += (T)p.y; z += (T)p.z; }


		/*!
		** \brief Add the same value for all coordinates to the vector
		** \param k The value to add to all coordinates
		*/
		template<typename U>
		void translate(const U k) { x += (T)k; y += (T)k; z += (T)k; }
		/*!
		** \brief Translate the point with relative coordinates
		** \param x1 The value to add to the X coordinate
		** \param y1 The value to add to the Y coordinate
		** \param z1 The value to add to the Z coordinate
		*/
		template<typename U, typename V, typename W>
		void translate(const U x1, const V y1, const W z1) { x += (T)x1; y += (T)y1; z += (T)z1; }
		/*!
		** \brief Translate the point with relative coordinates from another Point
		** \param p The values to add to the coordinates 
		*/
		template<typename U>
		void translate(const Vector3D<U>& p) { x += (T)p.x; y += (T)p.y; z += (T)p.z; }


		/*!
		** \brief Calculate the mean between two points
		**
		** The calling object is modified to store the value
		**
		** \param p Point to compute the mean with
		*/
		template<typename U>
		void mean(const Vector3D<U>& p)
		{
		  x = (T) ((x + p.x) / 2.0f);
		  y = (T) ((y + p.y) / 2.0f);
		  z = (T) ((z + p.z) / 2.0f);
		}
		/*!
		** \brief Calculate the mean between two points
		**
		** The calling object is modified to store the value
		**
		** \param p1 Point to compute the mean with
		** \param p2 Second point to compute the mean with
		** \return Always *this
		*/
		template<typename U, typename V>
		Vector3D<T>& mean(const Vector3D<U>& p1, const Vector3D<V>& p2)
		{
		  x = (T) ((p1.x + p2.x) / 2.0f);
		  y = (T) ((p1.y + p2.y) / 2.0f);
		  z = (T) ((p1.z + p2.z) / 2.0f);
		  return *this;
		}
		/*!
		** \brief Calculate the mean between two points
		**
		** \param p1 First point
		** \param p2 Second point
		** \return A new instance of Vector3D
		*/
		template<typename U, typename V>
		static Vector3D<T>& Mean(const Vector3D<U>& p1, const Vector3D<V>& p2)
		{
		  return Vector3D<T>().mean(p1, p2);
		}


		//! \name Operators
		//{

		/*!
		** \brief Reset all coordinates
		**
		** \param x1 The new value for the X coordinate
		** \param y1 The new value for the Y coordinate
		** \param z1 The new value for the Z coordinate
		** \see move()
		*/
		template<typename U, typename V, typename W>
		void operator () (const U x1, const V y1, const W z1) { x = (T)x1; y = (T)y1; z = (T)z1; }
		/*!
		** \brief Copy all coordinates from another vector
		**
		** \param v The coordinates to copy
		**
		** \see ()
		*/
		template<typename U>
		void operator () (const Vector3D<U>& v) { x = (T)v.x; y = (T)v.y; z = (T)v.z; }
		

		/*!
		** \brief Translate the point with the same value for all coordinates
		**
		** \param k The value to add to all coordinates
		** \return Always *this
		**
		** \see translate()
		*/
		template<typename U>
		Vector3D<T>& operator += (const U k) { x += (T)k; y += (T)k; z += (T)k; return (*this); }
		/*!
		** \brief Translate the point with relative coordinates
		**
		** \param p The values to add to coordinates
		** \return Always *this
		**
		** \see translate()
		*/
		template<typename U>
		Vector3D<T>& operator += (const Vector3D<U>& p) { x += (T)p.x; y += (T)p.y; z += (T)p.z; return (*this); }

		/*!
		** \brief Comparison operator (equal with)
		**
		** \param rhs The other point to compare with
		** \return True if the two points are equal
		*/
		template<typename U> bool operator == (const Vector3D<U>& rhs) const
		{ return (T)rhs.x == x && (T)rhs.y == y && (T)rhs.z == z; }

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param rhs The other point to compare with
		** \return True if the two points are not equal
		*/
		template<typename U> bool operator != (const Vector3D<U>& rhs) const
		{ return !(*this == rhs); }

		/*!
		** \brief Assign new values for all coordinates from another vector
		**
		** \param p The new coordinates
		** \return Always *this
		**
		** \see move()
		*/
		template<typename U>
		Vector3D<T>& operator = (const Vector3D<U>& p) { x = (T)p.x; y = (T)p.y; z = (T)p.z; return (*this); }

		//} Operators


		/*!
		** \brief Print the vector
		**
		** \param out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const
		{
			out << "(" << x << "," << y << "," << z << ")";
			return out;
		}


	public:
		//! X component
		T x;
		//! Y component
		T y;
		//! Z component
		T z;

	}; // class Vector3D


} // Gfx
} // Yuni



//! \name Operator overload for stream printing
//@{

template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Vector3D<T>& v)
{ return v.print(out); }

template<typename T>
inline const Yuni::Gfx::Vector3D<T> operator + (const Yuni::Gfx::Vector3D<T>& lhs, const Yuni::Gfx::Vector3D<T>& rhs)
{ return Yuni::Gfx::Vector3D<T>(lhs) += rhs; }

//@}


#endif // __YUNI_GFX_VECTOR3D_H__
