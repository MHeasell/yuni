#ifndef __YUNI_GFX_POINT2D_H__
# define __YUNI_GFX_POINT2D_H__

# include <iostream>
# include <yuni/misc/math.h>



namespace Yuni
{
namespace Gfx
{


    /*! \class Point2D
    **
    ** \brief Represents a 2D-point
    */
    template<typename T = float>
    class Point2D
    {
    public:
        //! \name Constructors & Destructor
        //{
        //! Default constructor
        Point2D() : x(0), y(0) {}
        /*!
        ** \brief Constructor
        ** \param x1 The default x coordinate
        ** \param y1 The default y coordinate
        */
        Point2D(const T x1, const T y1): x(x1), y(y1) {}
        //! Constructor by copy
        Point2D(const Point2D<T>& p) : x(p.x), y(p.y) {}
        //! Destructor
        virtual ~Point2D() {}
        //}

        //! Reset the point to origin
        Point2D<T>& reset() {x = y = 0; return *this;}


        /*!
        ** \brief Move the point to new coordinates
        ** 
        ** \param x1 The new X coordinate
        ** \param y1 The new Y coordinate
        */
        void move(const T x1, const T y1) { x = x1; y = y1; }
        /*!
        ** \brief Move the point to new coordinates
        ** \param p The new coordinates
        */
        void move(const Point2D& p) { x = p.x; y = p.y; }


        /*!
        ** \brief Translate the point with the same value for all coordinates
        **
        ** \param k The value to add to all coordinates
        */
        void translate(const T k) { x += k; y += k; }
        /*!
        ** \brief Translate the point with relative coordinates
        **
        ** \param x1 The value to add to the x coordinate
        ** \param y1 The value to add to the y coordinate
        */
        void translate(const T x1, T y1) { x += x1; y += y1; }
        /*!
        ** \brief Translate the point with relative coordinates from another Point
        ** \param p The values to add to the coordinates 
        */
        void translate(const Point2D& p) { x += p.x; y += p.y; }

        /*!
        ** \brief Calculate the mean between two points
        **
        ** The calling object is modified to store the value
        **
        ** \param p Point to compute the mean with
        */
        void mean(const Point2D& p)
        {
          x = (x + p.x) / 2.0f;
          y = (y + p.y) / 2.0f;
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
        Point2D& mean(const Point2D& p1, const Point2D& p2)
        {
          x = (p1.x + p2.x) / 2.0f;
          y = (p1.y + p2.y) / 2.0f;
          return *this;
        }
        /*!
        ** \brief Calculate the mean between two points
        **
        ** \param p1 First point
        ** \param p2 Second point
        ** \return A new instance of Point3D
        */
        static Point2D& Mean(const Point2D& p1, const Point2D& p2)
        {
          return Point2D().mean(p1, p2);
        }


        /*!
        ** \brief Get if the point is close to another point
        **
        ** \param rhs The other point
        ** \param delta Delta value
        */
        bool closeTo(const Point2D<T>& rhs, const T delta) const
        { return Math::Abs(x-rhs.x) < delta && Math::Abs(y-rhs.y) < delta; }

        /*!
        ** \brief Get if the point is close to another point
        **
        ** \param x1 The X coordinate of the other point
        ** \param y1 The Y coordinate of the other point
        ** \param delta Delta value
        */
        bool closeTo(const T x1, const T y1, const T delta) const
        { return Math::Abs(x-x1) < delta && Math::Abs(y-y1) < delta; }



        //! \name Operators
        //{

        /*!
        ** \brief Reset all coordinates
        **
        ** \param x1 The new value for the x coordinate
        ** \param y1 The new value for the y coordinate
        ** \see move()
        */
        void operator () (const T x1, const T y1) { x = x1; x = y1; }
        /*!
        ** \brief Copy all coordinates from another point
        ** \param p The coordinates to copy
        ** \see move()
        */
        void operator () (const Point2D& p) { x = p.x; y = p.y; }
        

        /*!
        ** \brief Translate the point with the same value for all coordinates
        **
        ** \param k The value to add to all coordinates
        ** \return Always *this
        **
        ** \see translate()
        */
        Point2D& operator += (const T k) { x += k; y += k; return (*this); }
        /*!
        ** \brief Translate the point with relative coordinates
        **
        ** \param p Point to use as reference x and y for the translation
        ** \return Always *this
        **
        ** \see translate()
        */
        Point2D& operator += (const Point2D& p) { x += p.x; y += p.y; return (*this); }

        /*!
        ** \brief Comparison operator (equal with)
        **
        ** \param rhs The other point to compare with
        ** \return True if the two points are equal
        */
        bool operator == (const Point2D& rhs) const
        { return rhs.x == x && rhs.y == y; }

        /*!
        ** \brief Comparison operator (non equal with)
        **
        ** \param rhs The other point to compare with
        ** \return True if the two points are not equal
        */
        bool operator != (const Point2D& rhs) const
        { return !(*this == rhs); }

        /*!
        ** \brief Assign new values for all coordinates from another point
        **
        ** \param p The new coordinates
        ** \return Always *this
        **
        ** \see move()
        */
        Point2D& operator = (const Point2D& p) { x = p.x; y = p.x; return (*this); }

        //} Operators


        /*!
        ** \brief Print the point
        */
        std::ostream& print(std::ostream& out) const
        {
            out << "(" << x << "," << y << ")";
            return out;
        }


    public:
        //! X coordinate
        T x;
        //! Y coordinate
        T y;

    }; // class Point2D


} // Gfx
} // Yuni



//! name Operator overload for stream printing
//@{

template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Point2D<T>& p)
{ return p.print(out); }

template<typename T>
inline const Yuni::Gfx::Point2D<T> operator + (const Yuni::Gfx::Point2D<T>& lhs, const Yuni::Gfx::Point2D<T>& rhs)
{ return Yuni::Gfx::Point2D<T>(lhs) += rhs; }

//@}


#endif // __YUNI_GFX_POINT2D_H__
