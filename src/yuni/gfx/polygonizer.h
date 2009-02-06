#ifndef __YUNI_GFX_POLYGONIZER_H__
# define __YUNI_GFX_POLYGONIZER_H__

# include "../yuni.h"
# include "implicitsurface.h"
# include "mesh.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A polygonizer is the abstraction of an algorithm able to create a triangle mesh from an isosurface.
	** \ingroup Gfx3DAlgorithms 
	*/
	class Polygonizer
	{
	public:
		//! Constructor
		Polygonizer(const ImplicitSurface& surf): pSurface(surf)
		{}
		virtual ~Polygonizer() {}

		/*!
		** \brief Calculate the mesh from the isosurface
		**
		** The purpose is to find points which solve:
		**   Surface(Point) = isoValue
		** Then we create triangles and a mesh from these points.
		**
		** \param isoValue Value that defines the isosurface
		** \param granularity Refinement value for the algorithm
		** \return A new Mesh approximating the surface
		*/
		virtual Mesh* operator () (float isoValue, float granularity) = 0;

	protected:
		/*!
		** \brief Determine if a given point is inside or outside the surface
		**
		** Calculate the value of a point to determine if the point is inside or outside the surface.
		**
		** \param p Point to calculate
		** \param isoValue Border value for the surface
		** \return True if the point is inside the isosurface, false otherwise
		*/
		bool isInsideSurface(const Point3D<float>& p, float isoValue) const
		{
			return pSurface(p) >= isoValue;
		}

		//! The isosurface we want to polygonize
		const ImplicitSurface& pSurface;

	}; // Class Polygonizer

} // Gfx
} // Yuni

#endif // __YUNI_GFX_POLYGONIZER_H__
