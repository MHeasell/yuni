
#ifndef __LIB_3D_IMPLICITSURFMANAGER_H__
# define __LIB_3D_IMPLICITSURFMANAGER_H__

# include <vector>
# include "metaball.h"
# include "octree.h"

namespace W
{
namespace GUI3D
{

    /*! class ImplicitSurfManager
    ** 
    ** Manager for all implicit surface regions.
    */
    class ImplicitSurfManager
    {
    public:
        ImplicitSurfManager();
        ~ImplicitSurfManager();

        //! Create a new metaball
        MetaBall* addMetaBall(const Point& p, float density);
        MetaBall* addMetaBall(float x, float y, float z, float density);

        float calculateSurface();

    private:
        std::vector<MetaObject> pObjects;

    }; // class ImplicitSurfManager

} // GUI3D
} // W

#endif // __LIB_3D_IMPLICITSURFMANAGER_H__
