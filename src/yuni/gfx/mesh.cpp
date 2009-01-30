
#include "mesh.h"
#include "../private/gfx3d/irrlicht/irr.mesh.h"

namespace Yuni
{
namespace Gfx
{

	Mesh::Mesh()
	{
		pProxy = new Yuni::Private::Gfx::Irrlicht::Mesh();
	}

	Mesh::~Mesh()
	{
	  delete pProxy;
	}

	std::ostream& Mesh::print(std::ostream& out) const
	{
		out << "Mesh containing " << pTriangles.size() << " triangles." << std::endl;
		for (TriangleList::const_iterator it = pTriangles.begin(); it != pTriangles.end(); ++it)
			(*it)->print(out);
		return out;
	}

	std::ostream& Mesh::glPrint(std::ostream& out) const
	{
		for (TriangleList::const_iterator it = pTriangles.begin(); it != pTriangles.end(); ++it)
			(*it)->glPrint(out);
		return out;
	}


} // Gfx
} // Yuni
