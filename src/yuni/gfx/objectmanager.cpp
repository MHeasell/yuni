
#include "object3d.h"
#include "objectmanager.h"

namespace Yuni
{
namespace Gfx
{

	namespace
	{
		ObjectManager objectManager;
	} // Anonymous namespace


	SmartPtr<ObjectManager> ObjectManager::Instance()
	{
		return SmartPtr<ObjectManager>(objectManager);
	}


	void ObjectManager::registerObject(SmartPtr<Object3D>& obj)
	{
		pObjects[obj->ID()] = obj;
	}


} //Gfx
} //Yuni
