
#ifndef __YUNI_PRIVATE_GFX_IRRLICHT_MESH_H__
# define __YUNI_PRIVATE_GFX_IRRLICHT_MESH_H__

# include <vector>
# include "irr.h"
# include "../../../gfx/mesh.proxy.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Irrlicht
{
	/*!
	** \class Mesh
	** \brief This is the Irrlicht-specific representation of a mesh
	*/
	class Mesh: public Yuni::Private::Gfx::ProxyMesh
	{
	public:
		Mesh(): pIrrMesh(NULL)
		{}

		/*!
		** \brief Update the Irrlicht mesh from the Yuni mesh
		** \param triangles List of triangles that will feed the Irrlicht mesh
		*/
		virtual void update(const TriangleList& triangles);

	private:
		typedef std::vector<Yuni::SmartPtr<Yuni::Gfx::Triangle> > TriangleList;

		//! The Irrlicht mesh
		irr::scene::SMesh* pIrrMesh;
	};

} // Irrlicht
} // Gfx
} // Private
} // Yuni

#endif // __YUNI_PRIVATE_GFX_IRRLICHT_MESH_H__
