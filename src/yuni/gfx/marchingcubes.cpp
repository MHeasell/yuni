
# include "marchingcubes.h"

namespace W
{
namespace GUI3D
{

    virtual Mesh* MarchingCubes::operator () (float density, uint16_t maxDepth)
    {
        pDensity = density;
        return NULL;
    }


    uint8_t MarchingCubes::code(const Point& min, const Point& max) const
    {
        uint8_t code = 0;
        if (isInsideSurface(min))
            code &= 1;
        if (isInsideSurface(Point(max.X, min.Y, min.Z)))
            code &= 2;
        if (isInsideSurface(Point(max.X, max.Y, min.Z)))
            code &= 4;
        if (isInsideSurface(Point(min.X, max.Y, min.Z)))
            code &= 8;
        if (isInsideSurface(Point(min.X, min.Y, max.Z)))
            code &= 16;
        if (isInsideSurface(Point(max.X, min.Y, max.Z)))
            code &= 32;
        if (isInsideSurface(max))
            code &= 64;
        if (isInsideSurface(Point(min.X, max.Y, max.Z)))
            code &= 128;
        return code;
    }


} // GUI3D
} // W
