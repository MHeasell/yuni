
#include "implicitsurface.h"

namespace Yuni
{
namespace Gfx
{

	ImplicitSurface::ImplicitSurface()
	{
	}

	ImplicitSurface::~ImplicitSurface()
	{
	}

	/*! Create a new metaball
	** It becomes the responsibility of the ImplicitSurface, so
	** it must not be deleted elsewhere.
	*/
	MetaBall* ImplicitSurface::addMetaBall(const Point3D<float>& p, float density)
	{
		MetaBall* newMB = new MetaBall(p, density);
		pObjects.push_back(newMB);
		return newMB;
	}

	MetaBall* ImplicitSurface::addMetaBall(float x, float y, float z, float density)
	{
		MetaBall* newMB = new MetaBall(x, y, z, density);
		pObjects.push_back(newMB);
		return newMB;
	}

	/*! Calculate the density of a point regarding the isosurface
	** The density is the sum of all the densities of the metaobjects
	** defining the isosurface.
	*/
	float ImplicitSurface::operator()(const Point3D<float>& p) const
	{
		float res = 0.0f;
		for (std::vector<MetaObject*>::const_iterator it = pObjects.begin();
			it != pObjects.end();
			++it)
			res += (**it)(p);
		return res;
	}

} // Gfx
} // Yuni
