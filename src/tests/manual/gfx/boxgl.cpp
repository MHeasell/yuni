/*
 * WARNING: this file uses bare OpenGL calls for now, and until Application::Gfx3D and/or friends implement
 * methods to display something on the devices.
 *
 * This is mainly a sample to enable Loomchild to test his Polygonizers algorithms.
 *
 */
#include <stdexcept>
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/objectmodel.h>
#include <yuni/gfx/object3D.h>
#include <yuni/gfx/mesh.h>
#include <yuni/gfx/marchingcubes.h>
#include <yuni/gfx/metabox.h>

using namespace Yuni;
using namespace Yuni::Gfx;

/*
 * We define an object model for a box, that contains a generated mesh
 * We allow this mesh to be replaced by another one
 */
class BoxModel: public ObjectModel
{
public:
	BoxModel(Mesh::Ptr& mesh)
		: ObjectModel(Skeleton::Ptr(new Skeleton(mesh, Vector3D<>(), Vector3D<>())))
	{
	}

	void mesh(Mesh::Ptr& newMesh)
	{
		setSkeleton(Skeleton::Ptr(new Skeleton(newMesh, Vector3D<>(), Vector3D<>())));
	}
};

/*
 * We define an Object3D that represents a box, using the BoxModel
 */
class OurBox: public Object3D
{
private:
	//! Our vertices
	std::vector<Vertex> pVertices;
	//! Our indexes
	std::vector<uint16> pIndexes;
	//! Our Bounding box.
	BoundingBox<> pBox;
	//! The box
	MetaBox* pMetabox;

public:
	OurBox(ObjectModel::Ptr model)
		: Object3D(model)
	{
		pMetabox = new MetaBox(BoundingBox<>(
			Point3D<>(-8.0, -8.0, -8.0), Point3D<>(8.0, 8.0, 8.0)));
		updateMesh();
	}

	void render()
	{
		//drawIndexedTriangleList(&(pVertices[0]), pVertices.size(), &(pIndexes[0]), pIndexes.size() / 3);
	}

	virtual const BoundingBox<>& getBoundingBox() const
	{
		return pBox;
	}

private:

	void updateMesh()
	{
		ImplicitSurface surf;

		// Add the box to the surface
		surf.addSubSurface(pMetabox);

		// Create a mesh using marchingcubes with an isovalue of 0.05, and a 2.0 mesh size
		Mesh* mesh2 = MarchingCubes(surf)(0.05f, 1.0f);
		if (!mesh2)
			throw std::runtime_error("Polygonization failed.");

		const Mesh::TriangleList& tList = mesh2->triangles();

		int vertexCount = 0;
		pIndexes.clear();
		pVertices.clear();
		for (Mesh::TriangleList::const_iterator triangle = tList.begin(); triangle != tList.end(); ++triangle)
		{
			const Gfx::Vertex &tVertex1 = (*triangle)->vertex1();
			const Gfx::Vertex &tVertex2 = (*triangle)->vertex2();
			const Gfx::Vertex &tVertex3 = (*triangle)->vertex3();

			pVertices.push_back(tVertex1);
			if (vertexCount == 0)
				pBox.reset(tVertex1.position());
			else
				pBox.addPoint(tVertex1.position());
			pIndexes.push_back(vertexCount);

			pVertices.push_back(tVertex2);
			pIndexes.push_back(vertexCount + 1);
			pBox.addPoint(tVertex2.position());

			pVertices.push_back(tVertex3);
			pIndexes.push_back(vertexCount + 2);
			pBox.addPoint(tVertex3.position());

			vertexCount += 3;
		}
		delete mesh2;
	}
};


class MeshTestApplication : public Application::Gfx3D
{
public:
	MeshTestApplication(int argc, char* argv[])
		:Application::Gfx3D(argc, argv)
	{
		// We connect our own method to the event
		Gfx::Engine::Instance()->onFPSChanged.connect(this, &MeshTestApplication::onFPSChanged);
	}

	virtual ~MeshTestApplication()
	{
		// It is advised to disconnect all events at this stage
		destroyingObserver();
	}

	void onFPSChanged(int fps)
	{
		// The FPS count has changed
		// We will set the application title according to the new value
		this->title(String() << "Hello World ! - " << fps << " fps");
	}
};


int main(int argc, char* argv[])
{
	OurBox* boxObj = new OurBox(new BoxModel());

	/*
	 * Yuni main loop (disabled)
	 */
	MeshTestApplication app(argc, argv);
	app.execute();
	return app.exitCode();
}
