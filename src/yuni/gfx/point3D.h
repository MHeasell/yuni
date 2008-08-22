
#ifndef __YUNI_POINT3D_H__
# define __YUNI_POINT3D_H__

# include <iostream>

namespace Yuni
{
namespace Gfx
{


    /*! \class Point3d
    **
    ** \brief Represents a 3D-point
    */
    class Point3D
    {
    public:
        //! \name Constructors & Destructor
        //{
        //! Default constructor
        Point3D() : X(0.0f), Y(0.0f), Z(0.0f) {}
        /*!
        ** \brief Constructor
        ** \param x The default X coordinate
        ** \param y The default Y coordinate
        ** \param z The default Z coordinate
        */
        Point3D(float x, float y, float z): X(x), Y(y), Z(z) {}
        //! Constructor by copy
        Point3D(const Point3D& p) : X(p.X), Y(p.Y), Z(p.Z) {}
        //! Destructor
        virtual ~Point3D() {}
        //}


        //! Move the point to new coordinates
        void move(float x, float y, float z) { X = x; Y = y; Z = z; }
        void move(const Point3D& p) { X = p.X; Y = p.Y; Z = p.Z; }


        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        */
        void translate(float k) { X += k; Y += k; Z += k; }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        ** \param z The value to add to the Z coordinate
        */
        void translate(float x, float y, float z) { X += x; Y += y; Z += z; }
        /*!
        ** \brief Translate the point with relative coordinates from another Point
        ** \param p 
        */
        void translate(const Point3D& p) { X += p.X; Y += p.Y; Z += p.Z; }

        //! Calculate the mean between two points
        void mean(const Point3D& p)
        {
          X = (X + p.X) / 2.0f;
          Y = (Y + p.Y) / 2.0f;
          Z = (Z + p.Z) / 2.0f;
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
        void operator () (float x, float y, float z) { X = x; Y = y; Z = z; }
        /*!
        ** \brief Copy all coordinates from another point
        ** \param p The coordinates to copy
        ** \see move()
        */
        void operator () (const Point3D& p) { X = p.X; Y = p.Y; Z = p.Z; }
        

        /*!
        ** \brief Translate the point with the same value for all coordinates
        ** \param k The value to add to all coordinates
        ** \see translate()
        */
        Point3D& operator += (const float k) { X += k; Y += k; Z += k; return (*this); }
        /*!
        ** \brief Translate the point with relative coordinates
        ** \param x The value to add to the X coordinate
        ** \param y The value to add to the Y coordinate
        ** \param z The value to add to the Z coordinate
        ** \see translate()
        */
        Point3D& operator += (const Point3D& p) { X += p.X; Y += p.Y; Z += p.Z; return (*this); }

        /*!
        ** \brief Comparison operator
        ** \param rhs
        */
        bool operator == (const Point3D& rhs) const
        { return rhs.X == X && rhs.Y == Y && rhs.Z == Z; }

        bool operator != (const Point3D& rhs) const
        { return !(*this == rhs); }

        /*!
        ** \brief Assign new values for all coordinates from another point
        ** \param p The new coordinates
        ** \see move()
        */
        Point3D& operator = (const Point3D& p) { X = p.X; Y = p.Y; Z = p.Z; return (*this); }

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
        //! Z coordinate
        float Z;

    }; // class Point3D


} // Gfx
} // Yuni



//! Operator overload for stream printing
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Point3D& p)
{ return p.print(out); }

inline const Yuni::Gfx::Point3D operator + (const Yuni::Gfx::Point3D& lhs, const Yuni::Gfx::Point3D& rhs)
{ return Yuni::Gfx::Point3D(lhs) += rhs; }



#endif // __YUNI_POINT3D_H__
