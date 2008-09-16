
#ifndef __LIB_3D_MARCHINGCUBES_H__
# define __LIB_3D_MARCHINGCUBES_H__

# include "../yuni.h"
# include "polygonizer.h"
# include "implicitsurface.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \class MarchingCubes
	**
	** \brief Marching cubes approximates an implicit surface using smaller and smaller cubes
	**
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

		/*!
		** \brief Actually calculate the mesh from the isosurface.
		** \param density Value defining the isosurface's limit
		** \param maxDepth Maximum refinement depth for the algorithm
		** \return A triangle mesh approximating the isosurface
		*/
		virtual Mesh* operator () (float density, uint16 maxDepth);


	private:
		/*!
		** \brief Marching cubes polygonization algorithm implementation
		**
		** Marching cubes uses an 8-bit code to represent to which pattern
		** case a certain cube corresponds. Each bit corresponds to a corner
		** vertex of the cube.
		** Calculate this code for a cube.
		**
		** \param min Point of minimum x, y, z in the cube
		** \param max Point of maximum x, y, z in the cube
		*/
		uint8 code(const Point3D<float>& min, const Point3D<float>& max) const;

	}; // Class MarchingCubes

} // Gfx
} // Yuni

#endif // __YUNI_GFX_MARCHINGCUBES_H__
