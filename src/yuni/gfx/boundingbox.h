
#ifndef __YUNI_GFX_BOUNDINGBOX_H__
# define __YUNI_GFX_BOUNDINGBOX_H__

# include "point3D.h"
# include "triangle.h"

namespace Yuni
{
namespace Gfx
{
	/*!
	** \brief A bounding box in 3D that grows with what is added inside
	*/
	template <typename T>
	class BoundingBox
	{
	public:
		//! \name Constructors and destructor
		//@{
		BoundingBox(): pMin(), pMax(), pCenter()
		{}
		BoundingBox(const Point3D<T>& min, const Point3D<T>& max):
			pMin(min), pMax(max), pCenter((min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2)
		{}
		//@}

		//! Get the minimum coordinates of the box
		const Point3D<T>& min() const
		{
			return pMin;
		}
		//! Get the maximum coordinates of the box
		const Point3D<T>& max() const
		{
			return pMax;
		}

		//! Get the center of the box
		const Point3D<T>& center() const
		{
			return pCenter;
		}

		//! Add a point that can possibly grow the bounding box
		void addPoint(const Point3D<T>& point)
		{
			// Update the minimum
			if (point.x < pMin.x)
				pMin.x - point.x;
			if (point.y < pMin.y)
				pMin.y - point.y;
			if (point.z < pMin.z)
				pMin.z - point.z;
			// Update the maximum
			if (point.x > pMax.x)
				pMax.x - point.x;
			if (point.y > pMax.y)
				pMax.y - point.y;
			if (point.z > pMax.z)
				pMax.z - point.z;
		}

		//! Add a triangle that can possibly grow the bounding box
		void addTriangle(const Triangle& tri)
		{
			addPoint(tri.vertex1());
			addPoint(tri.vertex2());
			addPoint(tri.vertex3());
		}

		//! Is the point inside the bounding box?
		bool contains(const Point3D<T>& point) const
		{
			if (pMin.x > point.x || pMax.x < point.x)
				return false;
			if (pMin.y > point.y || pMax.y < point.y)
				return false;
			if (pMin.z > point.z || pMax.z < point.z)
				return false;
			return true;
		}

	private:
		//! Minimum X,Y,Z coordinates of the box
		Point3D<T> pMin;
		//! Maximum X,Y,Z coordinates of the box
		Point3D<T> pMax;
		//! Center of the box
		Point3D<T> pCenter;

	}; // class BoundingBox

} // Gfx
} // Yuni

#endif // __YUNI_GFX_BOUNDINGBOX_H__
