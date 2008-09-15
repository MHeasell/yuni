
#ifndef __YUNI_GFX_IMPLICITSURFACE_H__
# define __YUNI_GFX_IMPLICITSURFACE_H__

# include <vector>
# include "metaball.h"
# include "octree.h"

namespace Yuni
{
namespace Gfx
{

	/*! class ImplicitSurface
	**
	** An implicit surface or isosurface is defined
	** by metaobjects interacting with each other.
	**
	*/
	class ImplicitSurface
	{
	public:
		ImplicitSurface();
		~ImplicitSurface();

		/*! Create a new metaball
		** It becomes the responsibility of the ImplicitSurface, so
		** it must not be deleted elsewhere.
		*/
		MetaBall* addMetaBall(const Point3D<float>& p, float density);
		MetaBall* addMetaBall(float x, float y, float z, float density);

		float operator()(const Point3D<float>& p) const;

	private:
		std::vector<MetaObject*> pObjects;

	}; // class ImplicitSurface

} // Gfx
} // Yuni

#endif // __YUNI_GFX_IMPLICITSURFACE_H__
