# include "window.h"
# include "../theme.h"

namespace Yuni
{
namespace UI
{
namespace Control
{


	void Window::draw(DrawingSurface::Ptr& surface, bool root)
	{
		if (!pVisible)
			return;

		auto themeptr = Theme::Current();
		auto& theme = *themeptr;
		Point2D<int> pos(pPosition);
		// If the window is the root control, use absolute coordinates
		if (root)
			pos(0, 0);
		surface->beginRectangleClipping(pos.x, pos.y, pSize.x, pSize.y);
		surface->drawFilledRectangle(theme.borderColor, theme.windowColor,
			pos.x, pos.y, pSize.x, pSize.y, theme.borderWidth);
		// Draw the children
		drawChildren(surface);
		surface->endClipping();
		pModified = false;
	}



} // namespace Control
} // namespace UI
} // namespace Yuni
