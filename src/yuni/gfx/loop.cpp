
#include "loop.h"


namespace Yuni
{
namespace Gfx
{


	bool Loop::onLoop()
	{
		// Loop on all depth groups, starting with the lower depths (nearest to the root)
		UI::IControl::DepthSortedMap::iterator depthEnd = pModifiedControls.end();
		for (UI::IControl::DepthSortedMap::iterator depthIt = pModifiedControls.begin();
			 depthIt != depthEnd; ++depthIt)
		{
			UI::IControl::Map::iterator ctrlEnd = depthIt->second.end();
			for (UI::IControl::Map::iterator ctrlIt = depthIt->second.begin();
				 ctrlIt != ctrlEnd; ++ctrlIt)
			{
				UI::IControl::Ptr ctrl = ctrlIt->second;

				// Special treatment for windows
				// TODO: do not use a string comparison !
				if (ctrl->className() == "window")
				{
					Window::IWindow::Map::iterator windowIterator = pWindows.find(ctrl->id());

					Window::IWindow::Ptr window;
					// Check if the window is newly created
					if (windowIterator == pWindows.end())
					{
						UI::Window::Ptr uiWindowPtr = UI::IControl::Ptr::DynamicCast<UI::Window::Ptr>(ctrl);
						// It is not referenced yet, create an internal representation
						Window::IWindow::Ptr window = Window::Create(uiWindowPtr, device);
						if (!window)
							// TODO: do not fail silently ! Stop here ?
							continue;
						else
							// Reference it
							pWindows[ctrl->id()] = window;
					}
					else
						// Found
						window = windowIterator->second;
				}
			}
		}
		return true;
	}



} // namespace Gfx
} // namespace Yuni
