
#include "mesh.h"

#ifdef YUNI_EXTERNAL_3D_IRRLICHT
#include "../private/gfx3d/irrlicht/irr.mesh.h"
#endif
#ifdef YUNI_EXTERNAL_3D_OGRE
//#include "../private/gfx3d/ogre/ogre.mesh.h"
#endif


namespace Yuni
{
namespace Gfx
{

	Mesh::Mesh()
	{
		#ifdef YUNI_EXTERNAL_3D_IRRLICHT
		pProxy = new Yuni::Private::Gfx::Irrlicht::Mesh();
		#endif
		#ifdef YUNI_EXTERNAL_3D_OGRE
		//pProxy = new Yuni::Private::Gfx::Ogre::Mesh();
		#endif
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


} // namespace Gfx
} // namespace Yuni
