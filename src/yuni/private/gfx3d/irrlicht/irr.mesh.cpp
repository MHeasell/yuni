
#include "../../../yuni.h"
#include "../../../toolbox/string.h"
#include "../../../hash/dictionary.h"
#include "../../../gfx/vertex.h"
#include "irr.mesh.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Irrlicht
{
	

	

	class VertexWithIndex
	{
	private:
		static Yuni::Gfx::Vertex nullVertex;
	public:
		VertexWithIndex()
			:pIndex(0), pVertex(nullVertex)
		{}

		VertexWithIndex(const uint32 i, Yuni::Gfx::Vertex& v)
			:pIndex(i), pVertex(v)
		{}

		uint32 index() const {return pIndex;}
		Yuni::Gfx::Vertex& vertex() const {return pVertex;}

		VertexWithIndex& operator = (const VertexWithIndex& rhs)
		{
			pIndex = rhs.pIndex;
			pVertex = rhs.pVertex;
			return *this;
		}

	private:
		uint32 pIndex;
		Yuni::Gfx::Vertex& pVertex;
	};

	typedef Hash::Dictionary<VertexWithIndex> HashVertex;

	Yuni::Gfx::Vertex VertexWithIndex::nullVertex;


	namespace
	{
		inline void addVertex(HashVertex& hash, uint32& index,
			Yuni::Gfx::Vertex vertex, uint16 indices[])
		{
			const String key(vertex.toString());
			Hash::Dictionary<VertexWithIndex>::iterator f = hash.find(key);
			if (hash.end() == f)
			{
				// The vertex does not exist in the list
				hash[key] = VertexWithIndex(index, vertex);
				indices[index] = index; 
			}
			else
				// The vertex already exists in the list
				// TODO Oo
				indices[index] = (uint16)((f->second).index());
			++index;
		}
	}


	void Mesh::update(const TriangleList& triangles)
	{
		if (!pIrrMesh)
			pIrrMesh = new irr::scene::SMesh();

		/*
		// irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
		uint32 nbTriangles = triangles.size();

		Hash::Dictionary<int> hashTab;
		Hash::Dictionary<Yuni::Gfx::Vertex> hashVertices;
		uint32 count = 0;
		uint16* indices = new uint16[nbTriangles * 3];
		 */

		// The count of vertices
		const uint32 nbVertices = 3 * triangles.size();
		// The mesh for irrlicht
		irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
		// Vertex
		HashVertex hash;
		// All indices for each vertex
		uint16* indices = new uint16[nbVertices];

		// For each triangle
		uint32 index(0);
		TriangleList::const_iterator end = triangles.end();
		for (TriangleList::const_iterator i = triangles.begin(); i != end; ++i)
		{
			addVertex(hash, index, Yuni::Gfx::Vertex((*i)->vertex1()), indices);
			addVertex(hash, index, Yuni::Gfx::Vertex((*i)->vertex2()), indices);
			addVertex(hash, index, Yuni::Gfx::Vertex((*i)->vertex3()), indices);
		}


		/*
		for (uint32 i = 0; i < nbTriangles * 3 && count < nbTriangles * 3; ++i)
		{
			const Yuni::Gfx::Vertex& vertex = (i % 3 == 0) 
				? triangles[i % 3]->vertex1()
				: ((i % 3 == 1)
				   ? triangles[i % 3]->vertex2()
				   : triangles[i % 3]->vertex3());
			const String key(vertex.toString());
			if (hashTab.exists(key))
				indices[i] = hashTab[key];
			else
			{
				hashTab[key] = count;
				hashVertices[key] = vertex;
				indices[i] = count; 
				++count;
			}
		}
		*/

		buffer->Indices.set_used(nbVertices);
		for (uint32 i = 0; i < nbVertices; ++i)
			buffer->Indices[i] = indices[i];
		delete[] indices;

		buffer->Vertices.set_used(hash.size());
		HashVertex::const_iterator e = hash.end();
		for (HashVertex::const_iterator it = hash.begin(); it != e; ++it)
		{
			const Yuni::Gfx::Point3D<float>& p = (it->second).vertex().position();
			buffer->Vertices[it->second.index()] = irr::video::S3DVertex(p.x, p.y, p.z, 1, 1, 1, 128, 0, 0);
		}

		//	buffer->Vertices[0]  = irr::scene::video::S3DVertex(0,0,0, -1,-1,-1, cubeColour, 0, 1);
		// 	buffer->Vertices[1]  = irr::scene::video::S3DVertex(1,0,0,  1,-1,-1, cubeColour, 1, 1);
		// 	buffer->Vertices[2]  = irr::scene::video::S3DVertex(1,1,0,  1, 1,-1, cubeColour, 1, 0);
		// 	buffer->Vertices[3]  = irr::scene::video::S3DVertex(0,1,0, -1, 1,-1, cubeColour, 0, 0);
		// 	buffer->Vertices[4]  = irr::scene::video::S3DVertex(1,0,1,  1,-1, 1, cubeColour, 0, 1);
		// 	buffer->Vertices[5]  = irr::scene::video::S3DVertex(1,1,1,  1, 1, 1, cubeColour, 0, 0);
		// 	buffer->Vertices[6]  = irr::scene::video::S3DVertex(0,1,1, -1, 1, 1, cubeColour, 1, 0);
		// 	buffer->Vertices[7]  = irr::scene::video::S3DVertex(0,0,1, -1,-1, 1, cubeColour, 1, 1);
		// 	buffer->Vertices[8]  = irr::scene::video::S3DVertex(0,1,1, -1, 1, 1, cubeColour, 0, 1);
		// 	buffer->Vertices[9]  = irr::scene::video::S3DVertex(0,1,0, -1, 1,-1, cubeColour, 1, 1);
		// 	buffer->Vertices[10] = irr::scene::video::S3DVertex(1,0,1,  1,-1, 1, cubeColour, 1, 0);
		// 	buffer->Vertices[11] = irr::scene::video::S3DVertex(1,0,0,  1,-1,-1, cubeColour, 0, 0);

		buffer->BoundingBox.reset(0, 0, 0);

		for (uint32 i = 0; i < nbVertices; ++i)
		{
			// piko ? Scale or translation
			// buffer->Vertices[i].Pos -= irr::core::vector3df(0.5f, 0.5f, 0.5f);
			//			buffer->Vertices[i].Pos *= cubeSize;
			buffer->BoundingBox.addInternalPoint(buffer->Vertices[i].Pos);
		}
		pIrrMesh->addMeshBuffer(buffer);
	}


} // Irrlicht
} // Gfx
} // Private
} // Yuni
