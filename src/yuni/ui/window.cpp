
#include "window.h"


namespace Yuni
{
namespace UI
{

	void Window::updateComponentWL(const IComponent::ID& componentID) const
	{
		//if (pApplication)
		//	pApplication->updateComponentWL(componentID);
	}


	void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
		{
			pClosing = true;
			onClose();
		}
	}


} // namespace UI
} // namespace Yuni

