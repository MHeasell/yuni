
#ifndef __YUNI_GFX_G3D_VERTEX_H__
# define __YUNI_GFX_G3D_VERTEX_H__

# include <vector>
# include "yuni/gfx/point3D.h"

namespace Yuni
{
namespace Gfx
{
namespace G3D
{
	/*!
	** \brief An edge is a segment between two vertices
	** \see Edge
	*/
	class Edge;

	/*!
	** \brief A vertex is a point in space which is the start of two edges of a triangle in a mesh.
	*/
	class Vertex
	{
	public:
		//! \name Constructors and destructors
		//@{
		Vertex(): pCoord()
		{}
		template<typename U, typename V, typename W>
		Vertex(const U x, const V y, const W z): pCoord(x, y, z)
		{}
		~Vertex() {}
		//@}


	private:
		Edge::Vector pEdges;
		Yuni::Gfx::Point3D pCoord;

	}; // Vertex
 

} // G3D
} // Gfx
} // Yuni

#endif // __YUNI_GFX_G3D_VERTEX_H__
