
#include "controlcontainer.h"


namespace Yuni
{
namespace UI
{


	void IControlContainer::resizeWL(float& newWidth, float& newHeight)
	{
		ThreadingPolicy::MutexLocker lock(*this);
		// TODO: Resize children to fit in the parent's new dimensions
		(void) newWidth;
		(void) newHeight;
	}


	void IControlContainer::addChildWL(const IControl::Ptr& child)
	{
		pChildren[child->id()] = child;
	}


	bool IControlContainer::removeChildWL(const IControl::Ptr& child)
	{
		return removeChildWL(child->id());
	}


	bool IControlContainer::removeChildWL(IComponent::ID childID)
	{
		IControl::Map::iterator it = pChildren.find(childID);
		bool exists = (it != pChildren.end());
		if (exists)
			pChildren.erase(it);
		return exists;
	}



} // namespace UI
} // namespace Yuni

