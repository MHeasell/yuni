
#ifndef __YUNI_POINT3D_H__
# define __YUNI_POINT3D_H__

# include <iostream>

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
        ** \param x The default X coordinate
        ** \param y The default Y coordinate
        ** \param z The default Z coordinate
        */
        Point3D(const T x1, const T y1, const T z1): x(x1), y(y1), z(z1) {}
        //! Constructor by copy
        Point3D(const Point3D& p) : x(p.x), y(p.y), z(p.z) {}
        //! Destructor
        virtual ~Point3D() {}
        //}


        //! Move the point to new coordinates
        void move(const T x1, const T y1, const T z1) { x = x1; y = y1; z = z1; }
        void move(const Point3D& p) { x = p.x; y = p.y; z = p.z; }


        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        */
        void translate(const T k) { x += k; y += k; z += k; }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        ** \param z The value to add to the Z coordinate
        */
        void translate(float x1, float y1, float z1) { x += x1; y += y1; z += z1; }
        /*!
        ** \brief Translate the point with relative coordinates from another Point
        ** \param p 
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
        ** The calling object is modified to store the value
        ** \param p1 Point to compute the mean with
        ** \param p2 Second point to compute the mean with
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
        ** \param p1 First point
        ** \param p2 Second point
        */
        static Point3D& Mean(const Point3D& p1, const Point3D& p2)
        {
          return Point3D().mean(p1, p2);
        }



        //! \name Operators
        //{

        /*!
        ** \brief Reset all coordinates
        ** \param x The new value for the X coordinate
        ** \param y The new value for the Y coordinate
        ** \param z The new value for the Z coordinate
        ** \see move()
        */
        void operator () (const T x1, const T y1, const T z1) { x = x1; y = y1; z = z1; }
        /*!
        ** \brief Copy all coordinates from another point
        ** \param p The coordinates to copy
        ** \see move()
        */
        void operator () (const Point3D& p) { x = p.x; y = p.y; z = p.z; }
        

        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        ** \see translate()
        */
        Point3D& operator += (const T k) { x += k; y += k; z += k; return (*this); }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        ** \param z The value to add to the Z coordinate
        ** \see translate()
        */
        Point3D& operator += (const Point3D& p) { x += p.x; y += p.y; z += p.z; return (*this); }

        /*!
        ** \brief Comparison operator
        ** \param rhs
        */
        bool operator == (const Point3D& rhs) const
        { return rhs.x == x && rhs.y == y && rhs.z == z; }

        bool operator != (const Point3D& rhs) const
        { return !(*this == rhs); }

        /*!
        ** \brief Assign new values for all coordinates from another point
        ** \param p The new coordinates
        ** \see move()
        */
        Point3D& operator = (const Point3D& p) { x = p.x; y = p.y; z = p.z; return (*this); }

        //} Operators


        /*!
        ** \brief Print the point
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
