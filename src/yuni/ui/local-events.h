#ifndef __YUNI_UI_LOCAL_EVENTS_H__
# define __YUNI_UI_LOCAL_EVENTS_H__

# include "../yuni.h"
# include "fwd.h"
# include "../core/event.h"


namespace Yuni
{
namespace UI
{

	class LocalUIEvents
	{
	public:
		void clear();

		LocalUIEvents& operator = (const LocalUIEvents& rhs);

	public:
		Event<void (const GUID&, Window*)> onShowWindow;
		Event<void (const GUID&, const IComponent::ID&)> onHideWindow;
		Event<void (const GUID&, const IComponent::ID&)> onCloseWindow;
		Event<void (const GUID&, IComponent::Ptr)> onShowComponent;
		Event<void (const GUID&, const IComponent::ID&)> onHideComponent;
		Event<void (const GUID&, const IComponent::ID&)> onUpdateComponent;

	}; // class LocalUIEvents



} // namespace UI
} // namespace Yuni

# include "window.h"

#endif // __YUNI_UI_LOCAL_EVENTS_H__
