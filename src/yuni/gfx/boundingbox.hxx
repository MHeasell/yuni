#ifndef __YUNI_GFX_BOUNDINGBOX_HXX__
# define __YUNI_GFX_BOUNDINGBOX_HXX__


namespace Yuni
{
namespace Gfx
{

	template<typename T>
	void BoundingBox<T>::addPoint(const Point3D<T>& point)
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


	template<typename T>
	inline void BoundingBox<T>::addTriangle(const Triangle& tri)
	{
		addPoint(tri.vertex1());
		addPoint(tri.vertex2());
		addPoint(tri.vertex3());
	}


	template<typename T>
	inline bool BoundingBox<T>::contains(const Point3D<T>& point) const
	{
		if (pMin.x > point.x || pMax.x < point.x)
			return false;
		if (pMin.y > point.y || pMax.y < point.y)
			return false;
		if (pMin.z > point.z || pMax.z < point.z)
			return false;
		return true;
	}



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_BOUNDINGBOX_HXX__
