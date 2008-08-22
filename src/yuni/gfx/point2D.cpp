
#include "point2D.h"

namespace Yuni
{
namespace Gfx
{

    std::ostream& Point2D::print(std::ostream& out) const
    {
        out << "(" << x << "," << y << ")";
        return out;
    }


} // Gfx
} // Yuni
