
#include "object3D.h"
#include "scene.h"


namespace Yuni
{
namespace Gfx
{


	Object3D::ID Object3D::NextID()
	{
		static Object3D::ID sIndx = 0;
		return sIndx++;
	}


	Object3D::Object3D(Scene& scene, const String& name, const ObjectModel::Ptr& model)
		:pID(NextID()), pName(name), pModel(model), pSkeleton()
	{
		assert(NULL != pModel);
		pSkeleton = pModel->skeleton();
		scene.registerObject(this);
	}

	Object3D::Object3D(Scene& scene, const ObjectModel::Ptr& model)
		:pID(NextID()), pName(), pModel(model), pSkeleton()
	{
		assert(NULL != pModel);
		pSkeleton = pModel->skeleton();
		scene.registerObject(this);
	}


	Object3D::~Object3D()
	{}


	void Object3D::skeleton(const Skeleton::Ptr& newSkeleton)
	{
		pSkeleton = newSkeleton;
	}



} // namespace Gfx
} // namespace Yuni


