
#include "object3d.h"
#include "scene.h"

namespace Yuni
{
namespace Gfx
{
	// Definition of the static ID counter in Object3D
	uint64 Object3D::sNextID = 0;

	namespace
	{
		SmartPtr<Scene> scene;
	} // Anonymous namespace


	SmartPtr<Scene> Scene::Instance()
	{
		if (!scene)
			scene = new Scene();
		return scene;
	}


	void Scene::registerObject(const SmartPtr<Object3D>& obj)
	{
		if (pObjects.find(obj->id()) == pObjects.end())
			pObjects[obj->id()] = obj;
		else
			std::cerr << "Error in Scene::registerObject(): "
				<< "inserting existing object with ID "
				<< obj->id() << std::endl;
	}


} //Gfx
} //Yuni
