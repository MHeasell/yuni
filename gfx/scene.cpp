
#include <cassert>
#include "object3D.h"
#include "scene.h"


namespace Yuni
{
namespace Gfx
{



	void Scene::registerObject(Object3D* obj)
	{
		/* Assert */
		assert(NULL != obj && "A registered object cannot be null");

		ThreadingPolicy::MutexLocker locker(*this);
		if (pObjects.find(obj->id()) == pObjects.end())
			pObjects[obj->id()] = obj;
		else
		{
			std::cerr << "Error in Scene::registerObject(): inserting existing object with ID "
				<< obj->id() << std::endl;
		}
	}




} // namespace Gfx
} // namespace Yuni
