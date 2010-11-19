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

		// Loop on applications
		ApplicationWindowMap::iterator appEnd = pVisibleWindows.end();
		for (ApplicationWindowMap::iterator appIt = pVisibleWindows.begin();
			appIt != appEnd; ++appIt)
		{
			// Loop on windows
			WindowMap::iterator winEnd = appIt->second.end();
			for (WindowMap::iterator winIt = appIt->second.begin();
				winIt != winEnd; ++winIt)
			{
				// Manage events coming from the system windows
				winIt->second.second->pollEvents();
				// Close dying windows
				if (winIt->second.first->closing())
				{
					winIt->second.second->close();
					appIt->second.erase(winIt);
					continue;
				}
				// For the moment, always draw the surfaces
				winIt->second.second->refresh();
			}
		}

		return true;
	}


	bool Windows::showWindowDispatched(ShowWindowParams::Ptr params)
	{
		if (!params)
			return true;

		// Get parameters
		Application::GUID appID = params->applicationGUID;
		Window::Ptr window = params->window;

		if (!window || window->closing())
			return true;

		// Get all known visible windows for this application
		// The application will be automatically added if necessary
		WindowMap& applicationWindows = pVisibleWindows[appID];

		// Check that the window was not already known as visible
		if (applicationWindows.find(window->id()) == applicationWindows.end())
		{
			// Add the window to the application
			std::pair<Window*, Private::UI::Local::IWindow*>& pair = applicationWindows[window->id()];
			pair.first = Window::Ptr::WeakPointer(window);
			// Create the local representation
			pair.second = Private::UI::Local::IWindow::Create(window);
			pair.second->resize(window->x(), window->y());
		}

		// TODO : Inform the queue service to update the window on next onLoop()

		return true;
	}



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni
