
#ifndef __YUNI_GFX_G3D_EDGE_H__
# define __YUNI_GFX_G3D_EDGE_H__

# include <vector>
# include "yuni/gfx/g3d/vertex.h"

namespace Yuni
{
namespace Gfx
{
namespace G3D
{
    /*!
    ** \brief An edge is a segment between two vertices
    */
    class Edge
    {
    public:
        //! \name Constructors and destructors
        //@{
        Edge(const Vertex& v1, const Vertex& v2): pVertex1
        {}
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
          return (pVertex1 == other.vertex1 && pVertex2 == other.vertex2) ||
                 (pVertex1 == other.vertex2 && pVertex2 == other.vertex1);
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
        Vertex pVertex1;
        Vertex pVertex2;
    }; // Edge
 
} // G3D
} // Gfx
} // Yuni

#endif // __YUNI_GFX_G3D_EDGE_H__
