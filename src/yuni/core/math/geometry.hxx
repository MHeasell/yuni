
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
		float dotProduct = DotProduct(planeNormal, lineDirection);
		assert(Math::Abs(dotProduct) < YUNI_EPSILON);
		// Vector connecting the two origin points from line to plane
		Vector3D<T> lineToPlane(planePoint.x - linePoint.x, planePoint.y - linePoint.y, planePoint.z - linePoint.z);
		float factor = DotProduct(lineToPlane, planeNormal) / dotProduct;
		// Scale the direction by the found value
		Vector3D<T> direction(lineDirection);
		direction *= factor;
		// Move the line point along the line to the intersection
		Point3D<T> result(linePoint);
		result.translate(direction.x, direction.y, direction.z);
		return result;
	}


	template<typename T>
	inline Point3D<T> PointToLineProjection(const Point3D<T>& point,
		const Point3D<T>& linePoint, const Vector3D<T>& lineDirection)
	{
		Vector3D<> translation(lineDirection);
		translation.normalize();
		float dot = Vector3D<>::DotProduct(translation, Vector3D<>(linePoint, point));
		translation *= dot;
		Point3D<> projection(linePoint);
		projection.translate(translation.x, translation.y, translation.z);
		return projection;
	}


	template<typename T>
	inline Point3D<T> PointToPlaneProjection(const Point3D<T>& point,
		const Point3D<T>& planePoint, const Vector3D<T>& planeNormal)
	{
		// First project on a normal line to the plane
		Point3D<> pn = PointToLineProjection(point, planePoint, planeNormal);
		// Get the vector from the projection to the point
		Vector3D<> translation(pn, point);
		// Translate the plane origin by this vector
		Point3D<> projection(planePoint);
		projection.translate(translation.x, translation.y, translation.z);
		return projection;
	}


	template<typename T>
	inline T VectorAngle(const Vector3D<T>& start, const Vector3D<T>& destination)
	{
		return 0.0f;
	}



} // namespace Geometry
} // namespace Yuni
