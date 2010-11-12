
#include "window.h"


namespace Yuni
{
namespace UI
{

	void Window::updateComponentWL(const IComponent::ID& componentID) const
	{
		(*onUpdateComponent)(componentID);
	}

	void Window::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing && onShowWindow)
		{
			(*onShowWindow)(this);
		}
	}


	void Window::hide()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing && onHideWindow)
			(*onHideWindow)(pLocalID);
	}


	void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing && onCloseWindow)
		{
			pClosing = true;
			(*onCloseWindow)(pLocalID);
		}
	}


} // namespace UI
} // namespace Yuni

