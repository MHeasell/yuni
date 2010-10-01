
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



} // namespace UI
} // namespace Yuni

