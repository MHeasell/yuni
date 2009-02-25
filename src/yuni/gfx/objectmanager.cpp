
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
		return SmartPtr<ObjectManager>(globalEngine);
	}


	void ObjectManager::registerObject(SmartPtr<Object3D>& obj)
	{
		pObjects.
	}


} //Gfx
} //Yuni
