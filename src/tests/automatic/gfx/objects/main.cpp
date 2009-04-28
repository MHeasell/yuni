
#include <yuni/yuni.h>
#include <yuni/gfx/object3D.h>

using Namespace Yuni;

class Car: public Gfx::Object3D
{
public:
	Car(const String& name, const SmartPtr<ObjectModel>& model)
		: Object3D(name, model)
	{}
};

int main(void)
{
	SmartPtr<Mesh> mesh(new Mesh());
	Skeleton* skeleton = new Skeleton(mesh, Vector3D<float>(); Vector3D<float>());
	ObjectModel *model = new (SmartPtr<Skeleton>(skeleton));
	Car c("Titine", SmartPtr<ObjectModel>(model));
	return 0;
}
