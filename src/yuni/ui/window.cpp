
#include "window.h"


namespace Yuni
{
namespace UI
{

	void Window::updateComponentWL(const IComponent::ID& componentID) const
	{
		onUpdateComponent(componentID);
	}

	void Window::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
		{
			onShowWindow(this);
		}
	}


	void Window::hide()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
			onHideWindow(pLocalID);
	}


	void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
		{
			pClosing = true;
			onCloseWindow(pLocalID);
		}
	}


} // namespace UI
} // namespace Yuni

