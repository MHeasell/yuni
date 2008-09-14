
#ifndef __LIB_3D_MARCHINGCUBES_H__
# define __LIB_3D_MARCHINGCUBES_H__

# include "polygonizer.h"
# include "implicitsurface.h"

namespace W
{
namespace GUI3D
{

    /*! class MarchingCubes
    ** The Marching Cubes algorithm finds cubes intersecting the surface,
    ** and matches the cubes with certain patterns to find to which neighbour
    ** cubes the algorithm should propagate.
    */
    class MarchingCubes: public Polygonizer
    {
    public:
        //! Constructor
        MarchingCubes(ImplicitSurface& surf): Polygonizer(surf)
        {}
        virtual ~MarchingCubes() {}

        /*! Actually calculate the mesh from the isosurface.
	** \param density Value defining the isosurface's limit
	** \param maxDepth Maximum refinement depth for the algorithm
	** \return A triangle mesh approximating the isosurface
	*/
        virtual Mesh* operator () (float density, uint16_t maxDepth);


    private:
        /*! Marching cubes uses an 8-bit code to represent to which pattern
	** case a certain cube corresponds. Each bit corresponds to a corner
	** vertex of the cube.
	** Calculate this code for a cube.
	** \param min Point of minimum x, y, z in the cube
	** \param max Point of maximum x, y, z in the cube
	*/
        uint8_t code(const Point& min, const Point& max) const;

    }; // Class MarchingCubes

} // GUI3D
} // W

#endif // __LIB_3D_MARCHINGCUBES_H__
