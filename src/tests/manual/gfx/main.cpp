
#include <yuni/yuni.h>
#include <yuni/gfx/mesh.h>
#include <yuni/gfx/marchingcubes.h>
#include <yuni/gfx/metaball.h>



using namespace Yuni;
using namespace Yuni::Gfx;

int main(void)
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

	return 0;
}
