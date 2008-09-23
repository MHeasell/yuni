
#ifndef __YUNI_GFX_MESH_H__
# define __YUNI_GFX_MESH_H__

# include "triangle.h"
# include "../misc/sharedptr.h"

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
		Mesh() {}

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
		** \brief Make a fusion between two meshes
		**
		** For the moment, the process is a bit simplistic:
		** Take each triangle of one mesh and add it to the other,
		** and recalculate the edges from nothing
		*/
		void fusion(Mesh* /*mesh*/)
		{
			// TODO
		}

	protected:
		typedef std::vector<SharedPtr<Triangle> > TriangleList;

		//! The Mesh knows all the triangles that define it
		TriangleList pTriangles;
	};

} // Gfx
} // Yuni

#endif // __YUNI_GFX_MESH_H__
