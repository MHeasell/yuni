
#include "object3d.h"
#include "objectmanager.h"

namespace Yuni
{
namespace Gfx
{
	// Definition of the static ID counter in Object3D
	uint64 Object3D::sNextID = 0;

	namespace
	{
		SmartPtr<ObjectManager> objectManager;
	} // Anonymous namespace


	SmartPtr<ObjectManager> ObjectManager::Instance()
	{
		if (!objectManager)
			objectManager = new ObjectManager();
		return objectManager;
	}


	void ObjectManager::registerObject(const SmartPtr<Object3D>& obj)
	{
		pObjects[obj->id()] = *new SmartPtr<Object3D>(obj);
	}


} //Gfx
} //Yuni
