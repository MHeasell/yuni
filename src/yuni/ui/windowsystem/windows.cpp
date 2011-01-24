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
		// Prime the message structure
		MSG msg;
		PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

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
		const GUID& appID = params->applicationGUID;
		Window::Ptr& window = params->window;

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

		return true;
	}

	bool Windows::closeWindowDispatched(ModifyWindowParams::Ptr params)
	{
		if (!params)
			return true;

		// Get parameters
		const GUID& appID = params->applicationGUID;
		IComponent::ID& windowID = params->windowID;

		// Make sure the application is known
		ApplicationWindowMap::iterator appWindowIterator = pVisibleWindows.find(appID);
		if (appWindowIterator == pVisibleWindows.end())
			return true;

		WindowMap& applicationWindows = appWindowIterator->second;
		// Make sure that the window was already known as visible
		WindowMap::iterator windowIterator = applicationWindows.find(windowID);
		if (windowIterator == applicationWindows.end())
			return true;

		// Close the local window
		windowIterator->second.second->close();
		// Remove the pair
		applicationWindows.erase(windowIterator);

		return true;
	}


	bool Windows::resizeWindowDispatched(ResizeWindowParams::Ptr params)
	{
		std::cout << "width: " << params->width
				  << ", height: " << params->height
				  << std::endl;

		if (!params)
			return true;

		// Get parameters
		const GUID& appID = params->applicationGUID;
		IComponent::ID& windowID = params->windowID;
		float width = params->width;
		float height = params->height;

		// Make sure the application is known
		ApplicationWindowMap::iterator appWindowIterator = pVisibleWindows.find(appID);
		if (appWindowIterator == pVisibleWindows.end())
			return true;

		WindowMap& applicationWindows = appWindowIterator->second;
		// Make sure that the window was already known as visible
		WindowMap::iterator windowIterator = applicationWindows.find(windowID);
		if (windowIterator == applicationWindows.end())
			return true;

		// Resize the local window
		windowIterator->second.second->resize(width, height);
		windowIterator->second.second->refresh();
		return true;
	}


} // namespace WindowSystem
} // namespace UI
} // namespace Yuni
