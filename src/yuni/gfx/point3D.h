#ifndef __YUNI_POINT3D_H__
# define __YUNI_POINT3D_H__

# include <iostream>
# include <yuni/misc/math.h>



namespace Yuni
{
namespace Gfx
{


    /*! \class Point3D
    **
    ** \brief Represents a 3D-point
    */
    template<typename T = float>
    class Point3D
    {
    public:
        //! \name Constructors & Destructor
        //{
        //! Default constructor
        Point3D() : x(0), y(0), z(0) {}
        /*!
        ** \brief Constructor
        ** \param x1 The default X coordinate
        ** \param y1 The default Y coordinate
        ** \param z1 The default Z coordinate
        */
        Point3D(const T x1, const T y1, const T z1): x(x1), y(y1), z(z1) {}
        //! Constructor by copy
        Point3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}
        //! Destructor
        virtual ~Point3D() {}
        //}


        /*!
        ** \brief Move the point to new coordinates
        ** 
        ** \param x1 The new X coordinate
        ** \param y1 The new Y coordinate
        ** \param z1 The new Z coordinate
        */
        void move(const T x1, const T y1, const T z1) { x = x1; y = y1; z = z1; }
        /*!
        ** \brief Move the point to new coordinates
        ** \param p The new coordinates
        */
        void move(const Point3D& p) { x = p.x; y = p.y; z = p.z; }


        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        */
        void translate(const T k) { x += k; y += k; z += k; }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x1 The value to add to the X coordinate
        ** \param y1 The value to add to the Y coordinate
        ** \param z1 The value to add to the Z coordinate
        */
        void translate(float x1, float y1, float z1) { x += x1; y += y1; z += z1; }
        /*!
        ** \brief Translate the point with relative coordinates from another Point
        ** \param p The values to add to the coordinates 
        */
        void translate(const Point3D& p) { x += p.x; y += p.y; z += p.z; }


        /*!
        ** \brief Calculate the mean between two points
        ** The calling object is modified to store the value
        ** \param p Point to compute the mean with
        */
        void mean(const Point3D& p)
        {
          x = (x + p.x) / 2.0f;
          y = (y + p.y) / 2.0f;
          z = (z + p.z) / 2.0f;
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
        Point3D& mean(const Point3D& p1, const Point3D& p2)
        {
          x = (p1.x + p2.x) / 2.0f;
          y = (p1.y + p2.y) / 2.0f;
          z = (p1.z + p2.z) / 2.0f;
          return *this;
        }
        /*!
        ** \brief Calculate the mean between two points
        **
        ** \param p1 First point
        ** \param p2 Second point
        ** \return A new instance of Point3D
        */
        static Point3D& Mean(const Point3D& p1, const Point3D& p2)
        {
          return Point3D().mean(p1, p2);
        }


        /*!
        ** \brief Get if the point is close to another point
        **
        ** \param rhs The other point
        ** \param delta Delta value
        */
        bool closeTo(const Point3D<T>& rhs, const T delta) const
        { return Math::Abs(x-rhs.x) < delta && Math::Abs(y-rhs.y) < delta && Math::Abs(z-rhs.z) < delta; }

        /*!
        ** \brief Get if the point is close to another point
        **
        ** \param x1 The X coordinate of the other point
        ** \param y1 The Y coordinate of the other point
        ** \param z1 The Z coordinate of the other point
        ** \param delta Delta value
        */
        bool closeTo(const T x1, const T y1, const T z1, const T delta) const
        { return Math::Abs(x-x1) < delta && Math::Abs(y-y1) < delta && Math::Abs(z-z1) < delta; }


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
        void operator () (const T x1, const T y1, const T z1) { x = x1; y = y1; z = z1; }
        /*!
        ** \brief Copy all coordinates from another point
        **
        ** \param p The coordinates to copy
        **
        ** \see move()
        */
        void operator () (const Point3D& p) { x = p.x; y = p.y; z = p.z; }
        

        /*!
        ** \brief Translate the point with the same value for all coordinates
        **
        ** \param k The value to add to all coordinates
        ** \return Always *this
        **
        ** \see translate()
        */
        Point3D& operator += (const T k) { x += k; y += k; z += k; return (*this); }
        /*!
        ** \brief Translate the point with relative coordinates
        **
        ** \param p The values to add to coordinates
        ** \return Always *this
        **
        ** \see translate()
        */
        Point3D& operator += (const Point3D& p) { x += p.x; y += p.y; z += p.z; return (*this); }

        /*!
        ** \brief Comparison operator (equal with)
        **
        ** \param rhs The other point to compare with
        ** \return True if the two points are equal
        */
        bool operator == (const Point3D& rhs) const
        { return rhs.x == x && rhs.y == y && rhs.z == z; }

        /*!
        ** \brief Comparison operator (non equal with)
        **
        ** \param rhs The other point to compare with
        ** \return True if the two points are not equal
        */
        bool operator != (const Point3D& rhs) const
        { return !(*this == rhs); }

        /*!
        ** \brief Assign new values for all coordinates from another point
        **
        ** \param p The new coordinates
        ** \return Always *this
        **
        ** \see move()
        */
        Point3D& operator = (const Point3D& p) { x = p.x; y = p.y; z = p.z; return (*this); }

        //} Operators


        /*!
        ** \brief Print the point
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
        //! X coordinate
        T x;
        //! Y coordinate
        T y;
        //! Z coordinate
        T z;

    }; // class Point3D


} // Gfx
} // Yuni



//! \name Operator overload for stream printing
//@{

template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Point3D<T>& p)
{ return p.print(out); }

template<typename T>
inline const Yuni::Gfx::Point3D<T> operator + (const Yuni::Gfx::Point3D<T>& lhs, const Yuni::Gfx::Point3D<T>& rhs)
{ return Yuni::Gfx::Point3D<T>(lhs) += rhs; }

//@}


#endif // __YUNI_POINT3D_H__
