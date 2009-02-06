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
	** \brief Marching cubes approximates an implicit surface using smaller and smaller cubes
	** \ingroup Gfx3DAlgorithms
	**
	** The Marching Cubes algorithm finds cubes intersecting the surface,
	** and matches the cubes with certain patterns to find to which neighbour
	** cubes the algorithm should propagate.
	*/
	class MarchingCubes: public Polygonizer
	{
	public:
		//! Constructor
		MarchingCubes(const ImplicitSurface& surf)
			:Polygonizer(surf)
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
		//! \name Typedefs
		//@{
		typedef ImplicitSurface::PointList PointList;
		typedef std::vector<Triangle*> TriangleList;
		typedef std::queue<Point3D<float> > Queue;
		//@}

	private:
		//! Association table between the marching cubes case index and the edge configuration
		static const int sEdgeTable[256];

		//! Association table between the marching cubes case index and the vertices forming the facets to create
		static const int sTriangleTable[256][16];

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
		** \param vals The calculated values of the 8 vertices of the cell
		*/
		uint8 cubeIndex(float isoValue, const float vals[8]) const;

		/*!
		** \brief Create a cube having the given point as center
		** \param center Point to use as center
		** \param width Size of the cell's edges. Manages mesh precision
		** \returns A newly created cell with the given center and width
		*/
		BoundingBox<float> cellAroundPoint(const Point3D<float>& center, float width);

		/*!
		** \brief Do the polygonization of a single cell of the grid
		**
		** Nothing will be done if the surface does not intersect the cell
		** Otherwise, triangles will be computed using marching cubes
		**
		** Given a grid cell and an isolevel, calculate the triangular
		** facets required to represent the isosurface through the cell.
		** Return the number of triangular facets, the array "triangles"
		** will be loaded up with the vertices at most 5 triangular facets.
		** No triangle will be created if the cell is either totally above
		** of totally below the isolevel.
		**
		** \param isoValue Limit value for belonging in the surface or not
		** \param width Size of the cell's sides. Manages mesh precision
		** \param cell The cell we want to find the triangles for
		** \param triangles The created triangles will be added here (at the end)
		** \param pointQueue Queue in which to enqueue the neighbour cells center
		** \returns Number of triangles created on this cell, 0 if in the surface, -1 if outside the surface
		*/
		int polygoniseCell(float isoValue, float width, const BoundingBox<float>& cell,
			TriangleList& triangles, Queue& pointQueue) const;

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
