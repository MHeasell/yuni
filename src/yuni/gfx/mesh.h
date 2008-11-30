
#ifndef __YUNI_GFX_MESH_H__
# define __YUNI_GFX_MESH_H__

# include "../toolbox/smartptr/sharedptr.h"
# include "triangle.h"
# include "mesh.proxy.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief A mesh is a set of linked and spatially positioned triangles.
	**
	** Every 3D model has an associated mesh, on which textures are applied.
	** Even implicit surfaces have to be converted to meshes for display.
	*/
	class Mesh
	{
	public:
		//! Main Constructor
		Mesh();

		/*!
		** \brief Add a triangle to the mesh
		**
		** This will fail if the triangle exists already in the mesh,
		** and the edges and vertices have to be updated.
		**
		** \param tri Triangle to add
		*/
		void addTriangle(const SharedPtr<Triangle>& tri)
		{
			pTriangles.push_back(tri);
		}

		/*!
		** \brief Print the mesh
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const;

		/*!
		** \brief Update the library-specific representation with the new data
		**
		** This is not done automatically to avoid doing it uselessly
		** (for example if more changes will be done).
		*/
		void update()
		{
			pProxy->update(pTriangles);
		}

	protected:
		typedef std::vector<SharedPtr<Triangle> > TriangleList;

		//! The Mesh knows all the triangles that define it
		TriangleList pTriangles;

		//! Proxy for the library-specific representation
		Yuni::Private::Gfx::ProxyMesh* pProxy;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_MESH_H__
