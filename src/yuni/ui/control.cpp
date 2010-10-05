
#include "control.h"
#include "controlcontainer.h"

namespace Yuni
{
namespace UI
{


	IControl::~IControl()
	{
		// We are dying, tell the parent we cannot be his child anymore
		if (pParent)
			(*pParent) -= pID;
	}


	void IControl::parent(IControlContainer* newParent)
	{
		// If we already had a parent, tell him we do not want to be his child anymore
		if (pParent)
			(*pParent) -= pID;
		pParent = newParent;
	}



} // namespace UI
} // namespace Yuni

