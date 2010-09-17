
#include <algorithm>
#include "../core/stl/algorithm.h"
#include "implicitsurface.h"


namespace Yuni
{
namespace Gfx
{


	ImplicitSurface::~ImplicitSurface()
	{
		Yuni::Core::STL::DeleteAndClear<ImplicitSurface, SubSurfaces>(pSubSurfaces);
	}


	//! Get some good points that we know are inside the surface
	void ImplicitSurface::insidePoints(PointList& points) const
	{
		for (unsigned int i = 0; i < pSubSurfaces.size(); ++i)
		{
			PointList surfPoints;
			pSubSurfaces[i]->insidePoints(surfPoints);
			for (unsigned int j = 0; j < surfPoints.size(); ++j)
				points.push_back(surfPoints[j]);
		}
	}


	/*!
	** \brief Add a subsurface as a component of this implicit surface
	** It becomes the responsibility of the ImplicitSurface, so
	** it must not be deleted elsewhere.
	*/
	void ImplicitSurface::addSubSurface(ImplicitSurface* surf)
	{
		pSubSurfaces.push_back(surf);
	}


	/*!
	** \brief Calculate the density of a point regarding to the isosurface
	** The density is the sum of all the densities of the metaobjects
	** defining the isosurface.
	**
	** \param p Point to calculate the value for
	*/
	float ImplicitSurface::operator()(const Point3D<float>& p) const
	{
		float res = 0.0f;
		SubSurfaces::const_iterator end = pSubSurfaces.end();
		for (SubSurfaces::const_iterator it = pSubSurfaces.begin(); it != end; ++it)
			res += (*(*it))(p);
		return res;
	}



} // namespace Gfx
} // namespace Yuni
