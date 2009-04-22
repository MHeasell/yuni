
#include "object3d.h"
#include "objectmanager.h"

namespace Yuni
{
namespace Gfx
{

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


	void ObjectManager::registerObject(SmartPtr<Object3D>& obj)
	{
		// pObjects[obj->id()] = obj;
	}


} //Gfx
} //Yuni
