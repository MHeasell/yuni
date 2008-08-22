
#ifndef __YUNI_POINT2D_H__
# define __YUNI_POINT2D_H__

# include <iostream>

namespace Yuni
{
namespace Gfx
{


    /*! \class Point2d
    **
    ** \brief Represents a 2D-point
    */
    class Point2D
    {
    public:
        //! \name Constructors & Destructor
        //{
        //! Default constructor
        Point2D() : X(0.0f), Y(0.0f) {}
        /*!
        ** \brief Constructor
        ** \param x The default X coordinate
        ** \param y The default Y coordinate
        */
        Point2D(float x, float y): X(x), Y(y) {}
        //! Constructor by copy
        Point2D(const Point2D& p) : X(p.X), Y(p.Y) {}
        //! Destructor
        virtual ~Point2D() {}
        //}


        //! Move the point to new coordinates
        void move(float x, float y) { X = x; Y = y; }
        void move(const Point2D& p) { X = p.X; Y = p.Y; }


        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        */
        void translate(float k) { X += k; Y += k; }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        */
        void translate(float x, float y) { X += x; Y += y; }
        /*!
        ** \brief Translate the point with relative coordinates from another Point
        ** \param p 
        */
        void translate(const Point2D& p) { X += p.X; Y += p.Y; }

        //! Calculate the mean between two points
        void mean(const Point2D& p)
        {
          X = (X + p.X) / 2.0f;
          Y = (Y + p.Y) / 2.0f;
        }


        //! \name Operators
        //{

        /*!
        ** \brief Reset all coordinates
        ** \param x The new value for the X coordinate
        ** \param y The new value for the Y coordinate
        ** \see move()
        */
        void operator () (float x, float y) { X = x; Y = y; }
        /*!
        ** \brief Copy all coordinates from another point
        ** \param p The coordinates to copy
        ** \see move()
        */
        void operator () (const Point2D& p) { X = p.X; Y = p.Y; }
        

        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        ** \see translate()
        */
        Point2D& operator += (const float k) { X += k; Y += k; return (*this); }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        ** \see translate()
        */
        Point2D& operator += (const Point2D& p) { X += p.X; Y += p.Y; return (*this); }

        /*!
        ** \brief Comparison operator
        ** \param rhs
        */
        bool operator == (const Point2D& rhs) const
        { return rhs.X == X && rhs.Y == Y; }

        bool operator != (const Point2D& rhs) const
        { return !(*this == rhs); }

        /*!
        ** \brief Assign new values for all coordinates from another point
        ** \param p The new coordinates
        ** \see move()
        */
        Point2D& operator = (const Point2D& p) { X = p.X; Y = p.Y; return (*this); }

        //} Operators


        /*!
        ** \brief Print the point
        */
        std::ostream& print(std::ostream& out) const;


    public:
        //! X coordinate
        float X;
        //! Y coordinate
        float Y;

    }; // class Point2D


} // Gfx
} // Yuni



//! Operator overload for stream printing
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Point2D& p)
{ return p.print(out); }

inline const Yuni::Gfx::Point2D operator + (const Yuni::Gfx::Point2D& lhs, const Yuni::Gfx::Point2D& rhs)
{ return Yuni::Gfx::Point2D(lhs) += rhs; }



#endif // __YUNI_POINT2D_H__
