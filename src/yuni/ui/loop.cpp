
#include "loop.h"


namespace Yuni
{
namespace UI
{


	bool Loop::onLoop()
	{
		// Loop on all depth groups, starting with the lower depths (nearest to the root)
		IControl::DepthSortedMap::iterator depthEnd = pModifiedControls.end();
		for (IControl::DepthSortedMap::iterator depthIt = pModifiedControls.begin();
			 depthIt != depthEnd; ++depthIt)
		{
			IControl::Map::iterator ctrlEnd = depthIt->second.end();
			for (IControl::Map::iterator ctrlIt = depthIt->second.begin();
				 ctrlIt != ctrlEnd; ++ctrlIt)
			{
				IControl::Ptr ctrl = ctrlIt->second;

				// Special treatment for windows
				// TODO: do not use a string comparison !
				if (ctrl->className() == "window")
					if (updateWindow(ctrl))
						// TODO: do not fail silently ! Stop here ?
						continue;
			}
		}
		pModifiedControls.clear();
		return true;
	}


	void Loop::markControlAsModified(IControl::Ptr control)
	{
		size_t depth = control->depth();
		IControl::DepthSortedMap::iterator depthIt = pModifiedControls.find(depth);

		bool found = (depthIt == pModifiedControls.end());
		if (found)
			pModifiedControls[depth];

		IControl::Map& depthCategory = found ? (depthIt->second) : pModifiedControls[depth];

		IControl::Map::iterator controlIt = depthCategory.find(control->id());
		if (controlIt != depthCategory.end())
			return;

		depthCategory[control->id()] = control;
	}


	bool Loop::updateWindow(IControl::Ptr ctrl)
	{
		Gfx::Window::IWindow::Map::iterator windowIterator = pWindows.find(ctrl->id());

		Gfx::Window::IWindow::Ptr window;
		// Check if the window is newly created
		if (windowIterator == pWindows.end())
		{
			Window::Ptr uiWindowPtr = IControl::Ptr::DynamicCast<Window::Ptr>(ctrl);
			// It is not referenced yet, create an internal representation
			Gfx::Window::IWindow::Ptr window = Gfx::Window::Create(uiWindowPtr, device);
			if (!window)
				return false;
			else
				// Reference it
				pWindows[ctrl->id()] = window;
		}
		else
			// Found
			window = windowIterator->second;
		return true;
	}



} // namespace UI
} // namespace Yuni
