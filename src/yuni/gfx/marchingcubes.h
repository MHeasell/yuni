
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
		MarchingCubes(const ImplicitSurface& surf): Polygonizer(surf)
		{}
		virtual ~MarchingCubes() {}

		/*!
		** \brief Polygonise a whole mesh given an isosurface
		** \param density Value defining the isosurface's limit
		** \param granularity Refinement value for the algorithm
		** \return A triangle mesh approximating the isosurface
		*/
		virtual Mesh* operator () (float density, float granularity);

	private:
		//! Represents a cube as needed by the marching cubes algorithm
		struct Cube
		{
			Point3D<float> min;
			Point3D<float> max;
		};

	private:
		/*!
		** \brief Marching cubes special index [0..256] calculation
		**
		** Marching cubes uses an 8-bit code to represent to which pattern
		** case a certain cube corresponds. Each bit corresponds to a corner
		** vertex of the cube.
		** Calculate this code for a cube.
		**
		** \param min Point of minimum x, y, z in the cube
		** \param max Point of maximum x, y, z in the cube
		*/
		uint8 cubeIndex(const Point3D<float>& min, const Point3D<float>& max) const;

		/*
		** \brief Interpolate the point at which the surface cuts the edge
		** Linearly interpolate the position where an isosurface cuts
		** an edge between two vertices, each with their own scalar value
		*/
		Point3D<float> interpolateVertex(double isolevel, Point3D<float> p1, Point3D<float> p2,
			double valp1, double valp2) const;


	}; // Class MarchingCubes

} // Gfx
} // Yuni

#endif // __YUNI_GFX_MARCHINGCUBES_H__
