
#include "component.h"

namespace Yuni
{
namespace UI
{


	void IComponent::resize(float width, float height)
	{
		ThreadingPolicy::MutexLocker lock(*this);

		resizeWL(width, height);
	}



} // namespace UI
} // namespace Yuni
