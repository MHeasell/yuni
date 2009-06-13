#ifndef __YUNI_GFX_BOUNDINGBOX_H__
# define __YUNI_GFX_BOUNDINGBOX_H__

# include "../yuni.h"
# include "point3D.h"
# include "triangle.h"



namespace Yuni
{
namespace Gfx
{



	/*!
	** \brief A bounding box in 3D that grows with what is added inside
	** \ingroup Gfx
	*/
	template <typename T>
	class BoundingBox
	{
	public:
		//! \name Constructors and destructor
		//@{

		//! Default constructor
		BoundingBox();
		
		/*!
		** \brief Constructor
		*/
		BoundingBox(const Point3D<T>& min, const Point3D<T>& max);
		
		//@}

		/*!
		** \brief Get the minimum coordinates of the box
		*/
		const Point3D<T>& min() const {return pMin;}

		/*!
		** \brief Get the maximum coordinates of the box
		*/
		const Point3D<T>& max() const {return pMax;}

		/*!
		** \brief Get the center of the box
		*/
		const Point3D<T>& center() const {return pCenter;}

		/*!
		** \brief Add a point that can possibly grow the bounding box
		*/
		void addPoint(const Point3D<T>& point);

		/*!
		** \brief Add a triangle that can possibly grow the bounding box
		*/
		void addTriangle(const Triangle& tri);

		/*!
		** \brief Is the point inside the bounding box?
		*/
		bool contains(const Point3D<T>& point) const;

	private:
		//! Minimum X,Y,Z coordinates of the box
		Point3D<T> pMin;
		//! Maximum X,Y,Z coordinates of the box
		Point3D<T> pMax;
		//! Center of the box
		Point3D<T> pCenter;

	}; // class BoundingBox



} // namespace Gfx
} // namespace Yuni


# include "boundingbox.hxx"

#endif // __YUNI_GFX_BOUNDINGBOX_H__
