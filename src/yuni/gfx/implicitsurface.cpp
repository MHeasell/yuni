
#include "implicitsurface.h"

namespace Yuni
{
namespace Gfx
{
	ImplicitSurface::~ImplicitSurface()
	{
		while (!pSubSurfaces.empty())
		{
			ImplicitSurface* surf = pSubSurfaces.back();
			delete surf;
			pSubSurfaces.pop_back();
		}
	}

	//! Get some good points that we know are inside the surface
	const std::vector<Point3D<float> > ImplicitSurface::insidePoints() const
	{
		std::vector<Point3D<float> > points;
		for (unsigned int i = 0; i < pSubSurfaces.size(); ++i)
		{
			std::vector<Point3D<float> > surfPoints = pSubSurfaces[i]->insidePoints();
			for (unsigned int j = 0; j < surfPoints.size(); ++i)
				points.push_back(surfPoints[j]);
		}
		return std::vector<Point3D<float> >(points);
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
		for (std::vector<ImplicitSurface*>::const_iterator it = pSubSurfaces.begin();
			it != pSubSurfaces.end();
			++it)
			res += (**it)(p);
		return res;
	}

} // Gfx
} // Yuni
