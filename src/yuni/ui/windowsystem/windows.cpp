#include "windows.h"
#include "../local/window.h"
#include <cassert>

namespace Yuni
{
namespace UI
{
namespace WindowSystem
{


	bool Windows::onLoop()
	{
		return true;
	}


	bool Windows::showWindowDispatched(ShowWindowParams::Ptr& params)
	{
		if (!params)
			return true;

		Application::GUID appID = params->applicationGUID;
		Window::Ptr window = params->window;

		if (!window)
			return true;

		assert(pVisibleWindows.find(appID) != pVisibleWindows.end() && "Attempting to access non-existing application !");
		WindowMap& applicationWindows = pVisibleWindows[appID];

		if (applicationWindows.find(window->id()) != applicationWindows.end())
		{
			// Add the window to the application
			std::pair<Window*, Private::UI::Local::IWindow*>& pair = applicationWindows[window->id()];
			pair.first = Window::Ptr::WeakPointer(window);
			// Create the local representation
			pair.second = Private::UI::Local::IWindow::Create(window);
		}

		// TODO : Inform the queue service to update the window on next onLoop()

		return true;
	}



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni
