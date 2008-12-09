
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/mesh.h>
#include <yuni/gfx/marchingcubes.h>
#include <yuni/gfx/metaball.h>



using namespace Yuni;
using namespace Yuni::Gfx;




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
		// It is advised to disconnect all events at this stade
		this->disconnectAllNotifiers();
	}

	void onFPSChanged(int fps)
	{
		// The FPS count has changed
		// We will set the application title according the new value
		this->title(String() << "Hello World ! - " << fps << " fps");
	}
};




int main(int argc, char* argv[])
{
	// Create a stupid mesh with only one triangle
	Mesh mesh;
	SharedPtr<Triangle> tri(new Triangle(Vertex(0.0f, 0.0f, 0.0f),
		Vertex(0.0f, 4.0f, 0.0f), Vertex(3.0f, 0.0f, 0.0f)));
	mesh.addTriangle(tri);
	mesh.print(std::cout);

	// Create an implicitsurface containing one metaball centered on (0,0,0), density=1.0f
	ImplicitSurface surf;
	surf.addSubSurface(new MetaBall(Point3D<float>(0.0f, 0.0f, 0.0f), 1.0f));

	// Create a mesh using marchingcubes with an isovalue of 4, and a 1.0 mesh size
	Mesh* mesh2 = MarchingCubes(surf)(4.0f, 1.0f);
	if (!mesh2)
		return 1;
	mesh2->print(std::cout);
	mesh2->update();

	// Create another mesh using marchingcubes with an isovalue of 7, and a 0.2 mesh size
// 	mesh2 = MarchingCubes(surf)(7.0f, 0.2f);
// 	if (!mesh2)
// 		return 1;
// 	mesh2->print(std::cout);

	MeshTestApplication app(argc, argv);
	app.execute();
	return app.exitCode();
}
