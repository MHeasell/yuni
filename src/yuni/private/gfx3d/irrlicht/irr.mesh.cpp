
#include "../../../yuni.h"
#include "../../../toolbox/string.h"
#include "../../../hash/dictionary.h"
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
		if (!pIrrMesh)
			pIrrMesh = new irr::scene::SMesh();

		irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
		uint32 nbTriangles = triangles.size();

		Hash::Dictionary<int> hashTab;
		Hash::Dictionary<Yuni::Gfx::Vertex> hashVertices;
		uint32 count = 0;
		uint16* indices = new uint16[nbTriangles * 3];
		for (uint32 i = 0; i < nbTriangles * 3 && count < nbTriangles * 3; ++i)
		{
			const Yuni::Gfx::Vertex& vertex = (i % 3 == 0) ? triangles[i]->vertex1() :
				((i % 3 == 1) ? triangles[i]->vertex2() : triangles[i]->vertex3());
			SharedPtr<String> key = vertex.asString();
			if (hashTab.exists(*key))
				indices[i] = hashTab[*key];
			else
			{
				hashTab[*key] = count++;
				hashVertices[*key] = vertex;
				indices[i] = hashTab[*key];
			}
		}

		buffer->Indices.set_used(nbTriangles * 3);
		for (uint32 i = 0; i < nbTriangles * 3; ++i)
			buffer->Indices[i] = indices[i];
		delete indices;

		buffer->Vertices.set_used(hashTab.size());
		for (Hash::Dictionary<int>::const_iterator it = hashTab.begin(); it != hashTab.end(); ++it)
		{
			const Yuni::Gfx::Vertex& vertex = hashVertices[it->first];
			buffer->Vertices[it->second] = irr::video::S3DVertex(vertex.position().x, vertex.position().y, vertex.position().z, 1, 1, 1, 128, 0, 0);
		}
// 		buffer->Vertices[0]  = irr::scene::video::S3DVertex(0,0,0, -1,-1,-1, cubeColour, 0, 1);
// 		buffer->Vertices[1]  = irr::scene::video::S3DVertex(1,0,0,  1,-1,-1, cubeColour, 1, 1);
// 		buffer->Vertices[2]  = irr::scene::video::S3DVertex(1,1,0,  1, 1,-1, cubeColour, 1, 0);
// 		buffer->Vertices[3]  = irr::scene::video::S3DVertex(0,1,0, -1, 1,-1, cubeColour, 0, 0);
// 		buffer->Vertices[4]  = irr::scene::video::S3DVertex(1,0,1,  1,-1, 1, cubeColour, 0, 1);
// 		buffer->Vertices[5]  = irr::scene::video::S3DVertex(1,1,1,  1, 1, 1, cubeColour, 0, 0);
// 		buffer->Vertices[6]  = irr::scene::video::S3DVertex(0,1,1, -1, 1, 1, cubeColour, 1, 0);
// 		buffer->Vertices[7]  = irr::scene::video::S3DVertex(0,0,1, -1,-1, 1, cubeColour, 1, 1);
// 		buffer->Vertices[8]  = irr::scene::video::S3DVertex(0,1,1, -1, 1, 1, cubeColour, 0, 1);
// 		buffer->Vertices[9]  = irr::scene::video::S3DVertex(0,1,0, -1, 1,-1, cubeColour, 1, 1);
// 		buffer->Vertices[10] = irr::scene::video::S3DVertex(1,0,1,  1,-1, 1, cubeColour, 1, 0);
// 		buffer->Vertices[11] = irr::scene::video::S3DVertex(1,0,0,  1,-1,-1, cubeColour, 0, 0);

		buffer->BoundingBox.reset(0,0,0);

		for (uint32 i = 0; i < count; ++i)
		{
			buffer->Vertices[i].Pos -= irr::core::vector3df(0.5f, 0.5f, 0.5f);
//			buffer->Vertices[i].Pos *= cubeSize;
			buffer->BoundingBox.addInternalPoint(buffer->Vertices[i].Pos);
		}

		pIrrMesh->addMeshBuffer(buffer);
	}


} // Irrlicht
} // Gfx
} // Private
} // Yuni
