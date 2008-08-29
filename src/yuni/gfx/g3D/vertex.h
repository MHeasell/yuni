
#ifndef __YUNI_GFX_G3D_VERTEX_H__
# define __YUNI_GFX_G3D_VERTEX_H__

# include <vector>
# include "../point3D.h"

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
		Vertex(): pPosition()
		{}
		Vertex(const Yuni::Gfx::Point3D& position): pPosition(position)
		{}
		template<typename U, typename V, typename W>
		Vertex(const U x, const V y, const W z): pCoord(x, y, z)
		{}
		~Vertex() {}
		//@}


		/*!
		** \brief Comparison operator (equal with)
		**
		** \param other The other vertex to compare with
		** \return True if the two vertices are coincident
		*/
		bool operator == (const Edge& other) const
		{
			return pPosition == other.position();
		}

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param other The other vertex to compare with
		** \return True if the two vertices are distinct
		*/
		bool operator != (const Edge& other) const
		{
			return !(*this == other);
		}


		//! Position of the vertex in space
		const Yuni::Gfx::Point3D& position() const
		{
			return pPosition;
		}

	private:
		Edge::Vector pEdges;
		Yuni::Gfx::Point3D pPosition;

	}; // Vertex


} // G3D
} // Gfx
} // Yuni

#endif // __YUNI_GFX_G3D_VERTEX_H__
