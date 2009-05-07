
#ifndef __YUNI_PRIVATE_GFX_OGRE_MESH_H__
# define __YUNI_PRIVATE_GFX_OGRE_MESH_H__

# include <vector>
# include "ogre.h"
# include "../../../gfx/mesh.proxy.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Ogre
{
	/*!
	** \class Mesh
	** \brief This is the Ogre-specific representation of a mesh
	*/
	class Mesh: public Yuni::Private::Gfx::ProxyMesh
	{
	public:
		Mesh(): pOgreMesh(NULL)
		{}

		/*!
		** \brief Update the Ogre mesh from the Yuni mesh
		** \param triangles List of triangles that will feed the Ogre mesh
		*/
		virtual void update(const TriangleList& triangles);

	private:
		typedef std::vector<Yuni::SmartPtr<Yuni::Gfx::Triangle> > TriangleList;

		//! The Ogre mesh
		::Ogre::Mesh* pOgreMesh;
	};

} // Ogre
} // Gfx
} // Private
} // Yuni

#endif // __YUNI_PRIVATE_GFX_OGRE_MESH_H__
