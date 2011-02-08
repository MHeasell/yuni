
#include "control.h"
#include "controlcontainer.h"

namespace Yuni
{
namespace UI
{


	IControl::~IControl()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		// We are dying, tell the parent we cannot be his child anymore
		if (pParent)
			(*pParent) -= pLocalID;
	}


	void IControl::parentWL(const IControl::Ptr& newParent)
	{
		IControl* newParentAsControl = Ptr::WeakPointer(newParent);
		IControlContainer* newParentAsContainer = dynamic_cast<IControlContainer*>(newParentAsControl);
		if (newParentAsContainer != newParentAsControl || pParent == newParentAsContainer)
			return;

		// If we already had a parent, tell him we do not want to be his child anymore
		if (pParent)
			(*pParent) -= pLocalID;
		if (!newParent)
		{
			pParent = nullptr;
			pDepth = 0;
		}
		else
		{
			pParent = newParentAsContainer;
			pDepth  = 1 + pParent->depth();
			(*pParent) += this;
		}
	}


	void IControl::updateComponentWL(const IComponent::ID& componentID) const
	{
		// If the tree is not rooted in a window / application
		// there is no local representation to update, so give up.
		if (pParent)
			pParent->updateComponentWL(componentID);
	}




} // namespace UI
} // namespace Yuni

