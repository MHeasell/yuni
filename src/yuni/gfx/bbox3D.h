
#ifndef __YUNI_GFX_BBOX3D_H__
# define __YUNI_GFX_BBOX3D_H__

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
	class BBox3D
	{
	public:
		//! \name Constructors and destructor
		//@{
		BBox3D(): pMin(), pMax()
		{}
		BBox3D(const Point3D<T>& min, const Point3D<T>& max): pMin(min), pMax(max)
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

	private:
		//! Minimum X,Y,Z coordinates of the box
		Point3D<T> pMin;
		//! Maximum X,Y,Z coordinates of the box
		Point3D<T> pMax;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_BBOX3D_H__
