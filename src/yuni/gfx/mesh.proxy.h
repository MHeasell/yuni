#ifndef __YUNI_PRIVATE_GFX_MESH_PROXY_H__
# define __YUNI_PRIVATE_GFX_MESH_PROXY_H__

# include <vector>
# include "triangle.h"
# include "../core/smartptr/smartptr.h"



namespace Yuni
{
namespace Private
{
namespace Gfx
{


	/*!
	** \class ProxyMesh
	** \brief This is a proxy for the library-specific representation of a mesh
	*/
	class ProxyMesh
	{
	protected:
		typedef std::vector<Yuni::SmartPtr<Yuni::Gfx::Triangle> > TriangleList;

	public:
		//! Virtual destructor
		virtual ~ProxyMesh() {}

		/*!
		** \brief Update the library-specific mesh from the Yuni mesh
		** \param triangles List of triangles that will feed the library-specific mesh
		*/
		virtual void update(const TriangleList& triangles) = 0;

	}; // class ProxyMesh



} // namespace Gfx
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_GFX_MESH_PROXY_H__
