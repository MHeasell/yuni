
# include "marchingcubes.h"

namespace Yuni
{
namespace Gfx
{

	Mesh* MarchingCubes::operator () (float density, uint16 maxDepth)
	{
		pDensity = density;
		return NULL;
	}


	uint8 MarchingCubes::code(const Point3D<float>& min, const Point3D<float>& max) const
	{
		uint8 code = 0;
		if (isInsideSurface(min))
			code &= 1;
		if (isInsideSurface(Point3D<float>(max.x, min.y, min.z)))
			code &= 2;
		if (isInsideSurface(Point3D<float>(max.x, max.y, min.z)))
			code &= 4;
		if (isInsideSurface(Point3D<float>(min.x, max.y, min.z)))
			code &= 8;
		if (isInsideSurface(Point3D<float>(min.x, min.y, max.z)))
			code &= 16;
		if (isInsideSurface(Point3D<float>(max.x, min.y, max.z)))
			code &= 32;
		if (isInsideSurface(max))
			code &= 64;
		if (isInsideSurface(Point3D<float>(min.x, max.y, max.z)))
			code &= 128;
		return code;
	}


} // Gfx
} // Yuni
