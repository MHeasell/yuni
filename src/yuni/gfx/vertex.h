#ifndef __YUNI_GFX_VERTEX_H__
# define __YUNI_GFX_VERTEX_H__

# include <vector>
# include "point3D.h"
# include "vector3D.h"
# include "../misc/string.h"
# include "../misc/sharedptr.h"

namespace Yuni
{
namespace Gfx
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
		Vertex(const Point3D<float>& position): pPosition(position)
		{}
		template<typename U, typename V, typename W>
		Vertex(const U x, const V y, const W z): pPosition(x, y, z)
		{}
		~Vertex() {}
		//@}


		/*!
		** \brief Comparison operator (equal with)
		**
		** \param other The other vertex to compare with
		** \return True if the two vertices are coincident
		*/
		bool operator == (const Vertex& other) const
		{
			return pPosition == other.position();
		}

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param other The other vertex to compare with
		** \return True if the two vertices are distinct
		*/
		bool operator != (const Vertex& other) const
		{
			return !(*this == other);
		}


		//! Position of the vertex in space
		const Point3D<float>& position() const
		{
			return pPosition;
		}

		//! Get a string representing the object to use as hash key
		SharedPtr<String> asString() const
		{
			String* str = new String();
			(*str) << pPosition.x << " " << pPosition.y << " " << pPosition.z;
			return str;
		}

	private:
		typedef std::vector<SharedPtr<Edge> > EdgeList;

	private:
		//! Edges linked to this vertex
		EdgeList pEdges;

		//! Position of the vertex in space
		Point3D<float> pPosition;

		//! Normal of the vertex (useful for lighting)
		Vector3D<float> pNormal;

	}; // Vertex




} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_VERTEX_H__
