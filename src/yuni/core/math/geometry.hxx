
#include <cassert>

namespace Yuni
{
namespace Geometry
{


	template<typename T>
	inline Point3D<T> LinePlaneIntersection(const Point3D<T>& linePoint,
		const Vector3D<T>& lineDirection, const Point3D<T>& planePoint,
		const Vector3D<T>& planeNormal)
	{
		T dotProduct = Vector3D<T>::DotProduct(planeNormal, lineDirection);
		assert(Math::Abs(dotProduct) < YUNI_EPSILON);
		// Vector connecting the two origin points from line to plane
		Vector3D<T> lineToPlane(linePoint, planePoint);
		T factor = DotProduct(lineToPlane, planeNormal) / dotProduct;
		// Scale the direction by the found value
		Vector3D<T> direction(lineDirection);
		direction *= factor;
		// Move the line point along the line to the intersection
		Point3D<T> result(linePoint);
		result.translate(direction.x, direction.y, direction.z);
		return result;
	}


	template<typename T>
	inline bool SegmentIntersectsPlane(const Point3D<T>& startPoint, const Point3D<T>& endPoint,
		const Point3D<T>& planePoint, const Vector3D<T>& planeNormal)
	{
		Vector3D<T> planeToStart(planePoint, startPoint);
		Vector3D<T> planeToEnd(planePoint, endPoint);

		T startDot = Vector3D<T>::DotProduct(planeToStart, planeNormal);
		T endDot = Vector3D<T>::DotProduct(planeToEnd, planeNormal);
		// The two ends of the segment are on different sides of the plane if :
		// 1. either of the dot products is null (one of the points is in the plane) OR
		// 2. the signs of the dot products are opposite.
		return Math::Zero(startDot) || Math::Zero(endDot) ||
			(startDot > 0) != (endDot > 0);
	}


	template<typename T>
	inline Point3D<T> PointToLineProjection(const Point3D<T>& point,
		const Point3D<T>& linePoint, const Vector3D<T>& lineDirection)
	{
		Vector3D<T> translation(lineDirection);
		translation.normalize();
		T dot = Vector3D<T>::DotProduct(translation, Vector3D<T>(linePoint, point));
		translation *= dot;
		Point3D<T> projection(linePoint);
		projection.translate(translation.x, translation.y, translation.z);
		return projection;
	}


	template<typename T>
	inline Point3D<T> PointToPlaneProjection(const Point3D<T>& point,
		const Point3D<T>& planePoint, const Vector3D<T>& planeNormal)
	{
		// First project on a normal line to the plane
		Point3D<T> pn = PointToLineProjection(point, planePoint, planeNormal);
		// Get the vector from the projection to the point
		Vector3D<T> translation(pn, point);
		// Translate the plane origin by this vector
		Point3D<T> projection(planePoint);
		projection.translate(translation.x, translation.y, translation.z);
		return projection;
	}


	template<typename T>
	inline T VectorAngle(const Vector3D<T>& start, const Vector3D<T>& destination)
	{
		// TODO
		return T();
	}



} // namespace Geometry
} // namespace Yuni
