
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
			(*pParent) -= pID;
	}


	void IControl::parentWL(IControl::Ptr newParent)
	{
		if (pParent == newParent)
			return;

		// If we already had a parent, tell him we do not want to be his child anymore
		if (pParent)
			(*pParent) -= pID;
		if (!newParent)
		{
			pParent = nullptr;
			pDepth = 0;
		}
		else
		{
			pParent = newParent;
			pDepth  = 1 + pParent->depth();
			(*pParent) += this;
		}
	}



} // namespace UI
} // namespace Yuni

