#ifndef __YUNI_GFX_RECT_2D_H__
# define __YUNI_GFX_RECT_2D_H__

# include <iostream>
# include "point2D.h"



namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief 2D-Rectangle
	*/
	template<typename T>
	class Rect2D
	{
	public:
		//! \name Constructors
		//@{
		
		//! Default constructor
		Rect2D() : x1(0), y1(0), x2(0), y2(0) {}
		
		/*!
		** \brief Construct the rectangle to cover two 2D-points
		**
		** \param a The first point to cover
		** \param b The second point to cover
		*/
		template<typename U, typename V>
		Rect2D(const Point2D<U>& a, const Point2D<V>& b) { reset(a, b); }
		
		/*!
		** \brief Constructor with given coordinates
		**
		** \param ax1 The top-left X-coordinate
		** \param ay1 The top-left Y-coordinate
		** \param ax2 The bottom-right X-coordinate
		** \param ay2 The bottom-right Y-coordinate
		*/
		template<typename U>
		Rect2D(const U ax1, const U ay1, const U ax2, const U ay2)
			:x1((T)ax1), y1((T)ay1), x2((T)ax2), y2((T)ay2)
		{}
		
		/*!
		** \brief Construct the rectangle to cover two other rectangles
		**
		** \param a The first rectangle to cover
		** \param b The second rectangle to cover
		*/
		template<typename U, typename V>
		Rect2D(const Rect2D<U>& a, const Rect2D<V>& b) { reset(a, b); }

		//@} // Constructors

		//! Reset the rectangle coordinates
		Rect2D<T>& reset() { x1 = y1 = x2 = y2 = T(); return *this; }

		/*!
		** \brief Reset the rectangle coordinates to cover two 2D-points
		**
		** \param a The first point to cover
		** \param b The second point to cover
		*/
		template<typename U, typename V>
		Rect2D<T>& reset(const Point2D<U>& a, const Point2D<V>& b)
		{
			x1 = Math::Min( (T) a.x, (T) b.x);
			y1 = Math::Min( (T) a.y, (T) b.y);
			x2 = Math::Max( (T) a.x, (T) b.x);
			y2 = Math::Max( (T) a.y, (T) b.y);
			return *this;
		}

		/*!
		** \brief Reset the rectangle coordinates to cover two 2D-points
		**
		** \param a The first X-coordinate
		** \param b The first Y-coordinate
		** \param c The second X-coordinate
		** \param d The second Y-coordinate
		*/
		template<typename U, typename V, typename W, typename X>
		Rect2D<T>& reset(const U a, const V b, const W c, const X d)
		{
			x1 = Math::Min( (T) a, (T) c);
			y1 = Math::Min( (T) b, (T) d);
			x2 = Math::Max( (T) a, (T) c);
			y2 = Math::Max( (T) b, (T) d);
			return *this;
		}



		/*!
		** \brief Reset the rectangle coordinates to cover two other rectangles
		**
		** \param a The first rectangle to cover
		** \param b The second rectangle to cover
		*/
		template<typename U, typename V>
		Rect2D<T>& reset(const Rect2D<U>& a, const Rect2D<V>& b)
		{
			x1 = Math::Min( (T) Math::Min(a.x1, a.x2), (T) Math::Min(b.x1, b.y1) );
			y1 = Math::Min( (T) Math::Min(a.y1, a.y2), (T) Math::Min(b.y1, b.y1) );
			x2 = Math::Max( (T) Math::Max(a.x1, a.x2), (T) Math::Max(b.x1, b.y1) );
			y2 = Math::Max( (T) Math::Max(a.y1, a.y2), (T) Math::Max(b.y1, b.y1) );
			return *this;
		}

		/*!
		** \brief Get the equivalent Point2D for the top left
		*/
		template<typename U>
		Point2D<U> topLeft() const {return Point2D<U>((U)x1, (U)y1);}
		/*!
		** \brief Get the equivalent Point2D for the bottom right
		*/
		template<typename U>
		Point2D<U> bottomRight() const {return Point2D<U>((U)x2, (U)y2);}


		/*!
		** \brief Get the surface occupied by the rectangle
		*/
		T size() const {return Math::Abs(x2-x1) * Math::Abs(y2-y1);}

		/*!
		** \brief Get the width of the rectangle
		*/
		T width() const {return Math::Abs(x2-x1);}
		/*!
		** \brief Get the height of the rectangle
		*/
		T height() const {return Math::Abs(y2-y1);}


		//! \name Move the entire rect
		//@{

		/*!
		** \brief Move the entire rect
		**
		** \param ax1 The new top left X-coordinate
		** \param ay1 The new top left Y-coordinate
		*/
		template<typename U> void move(const U ax1, const U ay1)
		{
			x2 = (T)ax1 + (x2 - x1); y2 = (T)ay1 + (y2 - y1);
			x1 = (T)ax1; y1 = (T)ay1;
		}

		/*!
		** \brief Move the entire rect
		**
		** \param p The new top left coordinates
		*/
		template<typename U> void move(const Point2D<U>& p)
		{
			x2 = (T)p.x + (x2 - x1); y2 = (T)p.y + (y2 - y1);
			x1 = (T)p.x; y1 = (T)p.y;
		}

		/*!
		** \brief Move the entire rect
		**
		** \param ax1 The new top left X-coordinate
		** \param ay1 The new top left Y-coordinate
		*/
		template<typename U, typename V> void operator () (const U& ax1, const V& ay1) {move(ax1, ay1);}

		/*!
		** \brief Move the entire rect
		** \param p The new top left coordinates
		*/
		template<typename U> void operator () (const Point2D<U>& p) {move(p);}

		/*!
		** \brief Reset the rectangle coordinates to cover two 2D-points
		**
		** \param a The first point to cover
		** \param b The second point to cover
		*/
		template<typename U, typename V> void operator () (const Point2D<U>& a, const Point2D<V>& b)
		{ reset(a, b); }

		/*!
		** \brief Reset the rectangle coordinates to cover two other rectangles
		**
		** \param a The first rectangle to cover
		** \param b The second rectangle to cover
		*/
		template<typename U, typename V> void operator () (const Rect2D<U>& a, const Rect2D<V>& b)
		{ reset(a, b); }


		//@}


		//! \name Geometrical localisation
		//@{

		/*!
		** \brief Get if a point is contained inside the rect
		**
		** \param p The point
		** \return True if the point is contained inside the rect
		*/
		template<typename U> bool contains(const Point2D<U>& p) const
		{ return p.x >= x1 && p.y >= y1 && p.x <= x2 && p.y <= y2; }
		/*!
		** \brief Get if a point is contained inside the rect
		**
		** \param nx The X-coordinate of the point
		** \param ny The Y-coordinate of the point
		** \return True if the point is contained inside the rect
		*/
		template<typename U, typename V> bool contains(const U nx, const V ny) const
		{ return nx >= x1 && ny >= y1 && nx <= x2 && ny <= y2; }

		/*!
		** \brief Get if another rectangle is contained inside this rectangle
		**
		** \param r The rect to test if it is inside the rect
		** \return True if the rect `r` is inside the rect `this`
		*/
		template<typename U> bool contains(const Rect2D<U>& r) const
		{ return (contains(r.x1, r.y1) && contains(r.x2, r.y2)); }

		/*!
		** \brief Get if another rectangle collides with this rectangle
		*/
		template<typename U> bool collidedWith(const Rect2D<U>& r) const
		{ return (contains(r.x1, r.y1) || contains(r.x2, r.y2)); }

		//@} Geometrical localisation


		//! \name Assignment
		//@{

		/*!
		** \brief Move the entire rect
		** \param p The new top left coordinates
		** \return Always *this
		*/
		template<typename U> Rect2D<T>& operator = (const Point2D<U>& p)
		{move(p);return *this;}

		/*!
		** \brief Assign new values for all coordinates from another rect
		** \param p The new coordinates
		** \return Always *this
		*/
		template<typename U> Rect2D<T>& operator = (const Rect2D<U>& p)
		{x1 = (T)p.x1; y1 = (T)p.y1; x2 = (T)p.x2; y2 = (T)p.y2; return *this;}

		//@}


		//! \name Stream printing
		//@{
		/*!
		** \brief Print the point
		*/
		std::ostream& print(std::ostream& out) const
		{
			out << "(" << x1 << "," << y1 << ":" << x2 << "," << y2 << ")";
			return out;
		}
		//@}


		/*!
		** \brief Swap coordinates if needed to have x1/y1 at the top-left and
		** x2/y2 at the bottom-right
		*/
		void repair()
		{
			if (x2 < x1) Math::Swap(x1, x2);
			if (y2 < y1) Math::Swap(y1, y2);
		}

	public:
		//! The top left X-coordinate
		T x1;
		//! The top left Y-coordinate
		T y1;
		//! The bottom right X-coordinate
		T x2;
		//! The bottom right Y-coordinate
		T y2;

	}; // class Rect2D



} // Gfx
} // Yuni



//! name Operator overload for stream printing
//@{

template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Rect2D<T>& p)
{ return p.print(out); }

//@}



#endif // __YUNI_GFX_RECT_2D_H__
