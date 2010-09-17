
#ifndef __YUNI_GFX_MESH_H__
# define __YUNI_GFX_MESH_H__

# include "../core/smartptr/smartptr.h"
# include "triangle.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A mesh is a set of linked and spatially positioned triangles.
	** \ingroup Gfx
	**
	** Every 3D model has an associated mesh, on which textures are applied.
	** Even implicit surfaces have to be converted to meshes for display.
	*/
	class Mesh
	{
	public:
		typedef SmartPtr<Mesh> Ptr;
		//! Type for Triangle list
		typedef std::vector<Triangle::Ptr> TriangleList;

	public:
		//! Main Constructor
		Mesh();
		~Mesh();

		/*!
		** \brief Add a triangle to the mesh
		**
		** This will fail if the triangle exists already in the mesh,
		** and the edges and vertices have to be updated.
		**
		** \param tri Triangle to add
		*/
		void addTriangle(const Triangle::Ptr& tri) {pTriangles.push_back(tri);}

		/*!
		** \brief Print the mesh
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const;

		/*!
		** \brief Generate OpenGL code corresponding to this mesh
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& glPrint(std::ostream& out) const;

		/*!
		** \brief Access to the mesh's triangle list
		**
		** \return A const reference to the mesh's triangle list
		*/
		const TriangleList& triangles() const {return pTriangles;}

	protected:
		//! The Mesh knows all the triangles that define it
		TriangleList pTriangles;

	}; // class Mesh




} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_MESH_H__
