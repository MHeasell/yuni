
#include "component.h"
#include "local-events.h"


namespace Yuni
{
namespace UI
{

	void LocalUIEvents::clear()
	{
		onShowWindow = nullptr;
		onHideWindow = nullptr;
		onCloseWindow = nullptr;
		onResizeWindow = nullptr;
		onShowComponent = nullptr;
		onHideComponent = nullptr;
		onUpdateComponent = nullptr;
	}


	LocalUIEvents& LocalUIEvents::operator = (const LocalUIEvents& rhs)
	{
		onShowWindow = rhs.onShowWindow;
		onHideWindow = rhs.onHideWindow;
		onCloseWindow = rhs.onCloseWindow;
		onResizeWindow = rhs.onResizeWindow;
		onShowComponent = rhs.onShowComponent;
		onHideComponent = rhs.onHideComponent;
		onUpdateComponent = rhs.onUpdateComponent;
		return *this;
	}


} // namespace UI
} // namespace Yuni

