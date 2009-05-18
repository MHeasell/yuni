
#include <yuni/yuni.h>
#include <yuni/core/smartptr/smartptr.h>
#include <yuni/gfx/object3D.h>

using namespace Yuni;

class Wheel: public Gfx::Object3D
{
public:
	Wheel(const String& name, const SmartPtr<Gfx::ObjectModel>& model)
		: Gfx::Object3D(name, model)
	{}
};

class Car: public Gfx::Object3D
{
public:
	Car(const String& name, const SmartPtr<Gfx::ObjectModel>& model)
		: Gfx::Object3D(name, model)
	{}
};

int main(void)
{
	SmartPtr<Gfx::Mesh> mesh(new Gfx::Mesh());
	SmartPtr<Gfx::Skeleton> skeleton(new Gfx::Skeleton(mesh, Gfx::Vector3D<float>(), Gfx::Vector3D<float>()));
	SmartPtr<Gfx::ObjectModel> carModel(new Gfx::ObjectModel(skeleton));
	// Use the same skeleton. This is a stupid test.
	SmartPtr<Gfx::ObjectModel> wheelModel(new Gfx::ObjectModel(skeleton));

	Car* c = new Car("Titine", carModel);

	c->append(new Wheel("LeftForwardWheel", wheelModel));
	c->append(new Wheel("RightForwardWheel", wheelModel));
	*c += new Wheel("LeftRearWheel", wheelModel);
	*c << new Wheel("RightRearWheel", wheelModel);

	return 0;
}
