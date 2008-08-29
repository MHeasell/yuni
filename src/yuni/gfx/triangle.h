#ifndef __YUNI_GFX_G3D_TRIANGLE_H__
# define __YUNI_GFX_G3D_TRIANGLE_H__

# include "edge.h"



namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief A triangle is a 3-sided polygon
	**
	** The triangle is the base element for all meshes
	** It knows its edges, and its vertices.
	*/
	class Triangle
	{
	public:
		//! \name Constructors
        //@{
		Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3):
			pVertex1(v1), pVertex2(v2), pVertex3(v3)
		{}
		//! \brief Copy constructor
		Triangle(const Triangle& t):
			pVertex1(t.Vertex1), pVertex2(t.vertex2), pVertex3(t.Vertex3)
		{}
		//@}

		//! \name Accessors
		//@{
		const Vertex& Vertex1() const { return pVertex1; }
		const Vertex& Vertex2() const { return pVertex2; }
		const Vertex& Vertex3() const { return pVertex3; }
		//@}

	private:
		//! \brief Vertices
		Vertex pVertex1;
		Vertex pVertex2;
		Vertex pVertex3;

		//! \brief Edges
		// TODO

		//! \brief Surface normal
		Vector3D<float> pNormal;
	};


} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_G3D_TRIANGLE_H__
