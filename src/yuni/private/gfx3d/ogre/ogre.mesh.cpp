
#include "../../../yuni.h"
#include "../../../toolbox/string.h"
#include "../../../toolbox/hash/dictionary.h"
#include "../../../gfx/vertex.h"
#include "ogre.mesh.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Ogre
{
	void Mesh::update(const TriangleList& triangles)
	{
		if (!pOgreMesh)
			pOgreMesh = new ::Ogre::Mesh();
	}


} // Ogre
} // Gfx
} // Private
} // Yuni
