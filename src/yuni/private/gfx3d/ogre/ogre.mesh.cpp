#include "../../../yuni.h"
#include "../../../core/string.h"
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
		::Ogre::MeshManager* meshManager;

		//createOrRetrieve(const String &name, const String &group, bool isManual=false, ManualResourceLoader *loader=0, const NameValuePairList *params=0, HardwareBuffer::Usage vertexBufferUsage=HardwareBuffer::HBU_STATIC_WRITE_ONLY, HardwareBuffer::Usage indexBufferUsage=HardwareBuffer::HBU_STATIC_WRITE_ONLY, bool vertexBufferShadowed=true, bool indexBufferShadowed=true)
		if (!pOgreMesh)
		{
			::Ogre::ResourceManager::ResourceCreateOrRetrieveResult res(meshManager->createOrRetrieve("", "", true));
		}
	}


} // namespace Ogre
} // namespace Gfx
} // namespace Private
} // namespace Yuni
