
#include "../core/math/math.h"
#include "window.h"


namespace Yuni
{
namespace UI
{

	void Window::updateComponentWL(const IComponent::ID& componentID) const
	{
		pLocalEvents.onUpdateComponent(pApplicationGUID, componentID);
	}


	void Window::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
			pLocalEvents.onShowWindow(pApplicationGUID, this);
	}


	void Window::hide()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
			pLocalEvents.onHideWindow(pApplicationGUID, pLocalID);
	}


	void Window::close()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pClosing)
		{
			pClosing = true;
			pLocalEvents.onCloseWindow(pApplicationGUID, pLocalID);
		}
	}


	void Window::resizeWL(float& width, float& height)
	{
		// If nothing has changed, do nothing
		if (Math::Equals(pWidth, width) && Math::Equals(pHeight, height))
			return;

		IControlContainer::resizeWL(width, height);
		if (!pClosing)
			pLocalEvents.onResizeWindow(pApplicationGUID, pLocalID, width, height);
	}


	void Window::reconnect()
	{
		reconnectLocalEvents(pLocalEvents);
	}



} // namespace UI
} // namespace Yuni

