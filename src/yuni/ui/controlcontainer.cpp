
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


	void IControlContainer::addChildWL(const IControl::Ptr&)
	{
		pChildren[child->id()] = child;
	}


	bool IControlContainer::removeChildWL(const IControl::Ptr&)
	{
		pChildren.erase(child->id());
		return false;
	}


} // namespace UI
} // namespace Yuni

