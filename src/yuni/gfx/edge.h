#ifndef __YUNI_GFX_EDGE_H__
# define __YUNI_GFX_EDGE_H__

# include <vector>
# include <list>
# include "../yuni.h"
# include "vertex.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief An edge is a segment between two vertices
	*/
	class Edge
	{
	public:
		//! Vector of Edges
		typedef std::vector< SharedPtr<Edge> >  Vector;
		//! List of Edges
		typedef std::list< SharedPtr<Edge> >  List;

	public:
		//! \name Constructors and destructors
		//@{
		Edge() : pVertex1(), pVertex2() {}
		Edge(const Vertex& v1, const Vertex& v2) :pVertex1(v1), pVertex2(v2) {}
		~Edge() {}
		//@}


		//! \brief Access to the vertices composing the edge
		const Vertex& vertex1() const { return pVertex1; }
		const Vertex& vertex2() const { return pVertex2; }


		/*!
		** \brief Comparison operator (equal with)
		**
		** \param other The other edge to compare with
		** \return True if the two edges share the same points
		*/
		bool operator == (const Edge& other) const
		{
			return (pVertex1 == other.vertex1() && pVertex2 == other.vertex2()) ||
				(pVertex1 == other.vertex2() && pVertex2 == other.vertex1());
		}

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param other The other edge to compare with
		** \return True if the two edges do not share the same points
		*/
		bool operator != (const Edge& other) const
		{ return !(*this == other); }


	private:
		//! The first vertex
		Vertex pVertex1;
		//! The second vertex
		Vertex pVertex2;

	}; // Edge



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_EDGE_H__
