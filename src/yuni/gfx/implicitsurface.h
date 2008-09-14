
#ifndef __LIB_3D_IMPLICITSURFACE_H__
# define __LIB_3D_IMPLICITSURFACE_H__

# include <vector>
# include "metaball.h"
# include "octree.h"

namespace W
{
namespace GUI3D
{

    /*! class ImplicitSurface
    ** 
    ** An implicit surface or isosurface is defined
    ** by metaobjects interacting with each other.
    ** 
    */
    class ImplicitSurface
    {
    public:
        ImplicitSurface();
        ~ImplicitSurface();

        /*! Create a new metaball
        ** It becomes the responsibility of the ImplicitSurface, so
        ** it must not be deleted elsewhere.
        */
        MetaBall* addMetaBall(const Point& p, float density);
        MetaBall* addMetaBall(float x, float y, float z, float density);

	float operator()(const Point& p) const;

    private:
        std::vector<MetaObject*> pObjects;

    }; // class ImplicitSurface

} // GUI3D
} // W

#endif // __LIB_3D_IMPLICITSURFACE_H__
