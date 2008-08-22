
#include "point3D.h"

namespace Yuni
{
namespace Gfx
{

    std::ostream& Point3D::print(std::ostream& out) const
    {
        out << "(" << X << "," << Y << "," << Z << ")";
        return out;
    }


} // Gfx
} // Yuni
