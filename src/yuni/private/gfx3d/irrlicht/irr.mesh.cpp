
#include "irr.mesh.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Irrlicht
{

	void Mesh::update(const TriangleList& triangles)
	{
		irr::scene::IMeshBuffer* buffer = pIrrMesh->getMeshBuffer(0);
		if (!buffer)
			return;
		uint16* indices = buffer->getIndices();
		void* vertices = buffer->getVertices();
		for (TriangleList::const_iterator it = triangles.begin(); it != triangles.end(); ++it)
			;
	}


} // Irrlicht
} // Gfx
} // Private
} // Yuni
