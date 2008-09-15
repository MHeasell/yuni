
#ifndef __YUNI_GFX_IMPLICITSURFMANAGER_H__
# define __YUNI_GFX_IMPLICITSURFMANAGER_H__

# include <vector>
# include "metaball.h"
# include "octree.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \class ImplicitSurfManager
	** Manager for all implicit surface regions.
	*/
	class ImplicitSurfManager
	{
	public:
		ImplicitSurfManager();
		~ImplicitSurfManager();

		/*!
		** \brief Create a new metaball
		** \param p Center of the metaball
		** \param density Density of the metaball (~= radius)
		** \result The newly created MetaBall object
		*/
		MetaBall* addMetaBall(const Point& p, float density);
		/*!
		** \brief Create a new metaball
		** \param x X coordinate for the center of the metaball
		** \param y Y coordinate for the center of the metaball
		** \param z Z coordinate for the center of the metaball
		** \param density Density of the metaball (~= radius)
		** \result The newly created MetaBall object
		*/
		MetaBall* addMetaBall(float x, float y, float z, float density);

		float calculateSurface();

	private:
		std::vector<SharedPtr<MetaObject> > pObjects;

	}; // class ImplicitSurfManager

} // Gfx
} // Yuni

#endif // __YUNI_GFX_IMPLICITSURFMANAGER_H__
