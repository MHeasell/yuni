
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
		pModifiedControls.clear();
		return true;
	}


	void Loop::markControlAsModified(UI::IControl::Ptr control)
	{
		// TODO : Manage children for containers, use an iterator on IControlContainer ?

		size_t depth = control->depth();
		UI::IControl::DepthSortedMap::iterator depthIt = pModifiedControls.find(depth);

		bool found = (depthIt == pModifiedControls.end());
		if (found)
			pModifiedControls[depth];

		UI::IControl::Map& depthCategory = found ? (depthIt->second) : pModifiedControls[depth];

		UI::IControl::Map::iterator controlIt = depthCategory.find(control->id());
		if (controlIt != depthCategory.end())
			return;

		depthCategory[control->id()] = control;
	}



} // namespace Gfx
} // namespace Yuni
