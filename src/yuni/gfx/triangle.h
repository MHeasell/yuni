#ifndef __YUNI_GFX_TRIANGLE_H__
# define __YUNI_GFX_TRIANGLE_H__

# include "edge.h"
# include "vector3D.h"

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
		//! Copy constructor
		Triangle(const Triangle& t):
			pVertex1(t.vertex1()), pVertex2(t.vertex2()), pVertex3(t.vertex3())
		{}
		//@}

		//! \name Accessors
		//@{
		const Vertex& vertex1() const { return pVertex1; }
		const Vertex& vertex2() const { return pVertex2; }
		const Vertex& vertex3() const { return pVertex3; }
		//@}

		/*!
		** \brief Print the triangle
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const
		{
			out << "Triangle with vertices at:" << std::endl;
			out << pVertex1.position() << std::endl;
			out << pVertex2.position() << std::endl;
			out << pVertex3.position() << std::endl;
			return out;
		}

	private:
		//! Vertices
		Vertex pVertex1;
		Vertex pVertex2;
		Vertex pVertex3;

		//! Edges
		// TODO

		//! Surface normal
		Vector3D<float> pNormal;
	};


} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_TRIANGLE_H__
