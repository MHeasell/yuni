#ifndef __YUNI_GFX_POLYGONIZER_H__
# define __YUNI_GFX_POLYGONIZER_H__

# include "../yuni.h"
# include "implicitsurface.h"
# include "mesh.h"

namespace Yuni
{
namespace Gfx
{


	/*! \class Polygonizer
	**
	** A polygonizer is the abstraction of an algorithm
	** able to create a triangle mesh from an isosurface.
	*/
	class Polygonizer
	{
	public:
		//! Constructor
		Polygonizer(ImplicitSurface& surf): pSurface(surf)
		{}
		virtual ~Polygonizer() {}

		/*!
		** \brief Calculate the mesh from the isosurface
		**
		** The purpose is to find points which solve:
		**   Surface(Point) = density.
		** Then we create triangles and a mesh from these points.
		** 
		** \param density Value that defines the isosurface
		** \param maxDepth Maximum refinement depth for the algorithm
		** \return A new Mesh approximating the surface
		*/
		virtual Mesh* operator () (float density, uint16 maxDepth) = 0;

	protected:
		/*!
		** \brief Determine if a given point is inside or outside the surface
		**
		** Calculate the density of a point, and use the surface's density
		** to determine if the point is inside or outside the surface.
		**
		** \param p Point to calculate
		** \return True if the point is inside the isosurface, false otherwise
		*/
		bool isInsideSurface(const Point3D<float>& p) const
		{
			return pSurface(p) >= pDensity;
		}

		//! The isosurface we want to polygonize
		ImplicitSurface& pSurface;

		//! Density defining the isosurface
		float pDensity;

	}; // Class Polygonizer

} // Gfx
} // Yuni

#endif // __YUNI_GFX_POLYGONIZER_H__
