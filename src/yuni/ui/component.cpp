
#include "component.h"

namespace Yuni
{
namespace UI
{


	void IComponent::resize(float width, float height)
	{
		ThreadingPolicy::MutexLocker lock(*this);

		// The new size
		float nwWidth  = (width  > 0.f) ? width  : 0.f;
		float nwHeight = (height > 0.f) ? height : 0.f;

		resizeWL(nwWidth, nwHeight);

		// assigning the new size.
		pWidth  = nwWidth;
		pHeight = nwHeight;
	}



} // namespace UI
} // namespace Yuni

