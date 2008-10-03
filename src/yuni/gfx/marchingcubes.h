
#ifndef __LIB_3D_MARCHINGCUBES_H__
# define __LIB_3D_MARCHINGCUBES_H__

# include <vector>
# include <queue>
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
		** \param isoValue Value defining the isosurface's limit
		** \param granularity Refinement value for the algorithm
		** \return A triangle mesh approximating the isosurface
		*/
		virtual Mesh* operator () (float isoValue, float granularity);

	private:
		/*!
		** \brief Marching cubes special index [0..256] calculation
		**
		** Marching cubes uses an 8-bit code to represent to which pattern
		** case a certain cube corresponds. Each bit corresponds to a corner
		** vertex of the cube.
		** Calculate this code for a cube.
		**
		** \param isoValue Limit value for belonging in the surface or not
		** \param cell The cell we want to calculate the marching cubes special case for
		*/
		uint8 cubeIndex(float isoValue, const BoundingBox<float>& cell) const;

		/*!
		** \brief Create a cube having the given point as center
		** \param center Point to use as center
		** \param width Size of the edges of the cube
		** \returns A newly created cell with the given center and width
		*/
		BoundingBox<float> cellAroundPoint(const Point3D<float>& center, float width);

		/*!
		** \brief Enqueue the neighbour cells that are also cut by the surface
		** \param current Current center of the cell (cut by the surface)
		** \param edgeCase Value representing which edges of the cube are intersected
		** \param pointQueue Queue in which to enqueue the neighbour cells center
		*/
		void AddNeighboursToQueue(const Point3D<float> current, int edgeCase,
			std::queue<Point3D<float> >& pointQueue) const;

		/*!
		** \brief Do the polygonization of a single cell of the grid
		**
		** Nothing will be done if the surface does not intersect the cell
		** Otherwise, triangles will be computed using marching cubes
		**
		** \param isoValue Limit value for belonging in the surface or not
		** \param cell The cell we want to find the triangles for
		** \param triangles The created triangles will be added here (at the end)
		** \returns Number of triangles created on this cell
		*/
		unsigned int polygoniseCell(float isoValue, const BoundingBox<float>& cell,
			std::vector<Triangle*>& triangles) const;

		/*
		** \brief Interpolate the point at which the surface cuts the edge
		**
		** Linearly interpolate the position where an isosurface cuts
		** an edge between two vertices, each with their own scalar value
		*/
		Point3D<float> interpolateVertex(double isolevel,
			const Point3D<float>& p1, const Point3D<float>& p2,
			double valp1, double valp2) const;


	}; // Class MarchingCubes

} // Gfx
} // Yuni

#endif // __YUNI_GFX_MARCHINGCUBES_H__
