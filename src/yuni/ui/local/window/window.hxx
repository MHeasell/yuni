#ifndef __YUNI_UI_LOCAL_WINDOW_WINDOW_HXX__
# define __YUNI_UI_LOCAL_WINDOW_WINDOW_HXX__

# include "../../../core/string.h"
# include <cassert>

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace Window
{


	inline void IWindow::refresh()
	{
		if (!pRefreshRefCount)
			doRefresh();
	}


	inline void forceRefresh()
	{
		doRefresh();
	}


	inline void IWindow::beginUpdate()
	{
		++pRefreshRefCount;
	}


	inline void IWindow::endUpdate()
	{
		assert(pRefreshRefCount > 0);
		if (!--pRefreshRefCount)
          doRefresh();
	}


	template<class StringT>
	inline void IWindow::caption(const StringT& newString)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, IWindowCaption_InvalidTypeForBuffer);
		pCaption = newString;
		doUpdateCaption();
	}


	inline void IWindow::style(unsigned int flags)
	{
		pStyle = style;
		doUpdateStyle();
	}


	inline void IWindow::stayOnTop(bool alwaysOnTop)
	{
		pStayOnTop = alwaysOnTop;
		doUpdateStayOnTop();
	}


	inline void IWindow::backgroundColor(const Color& color)
	{
		pBackgroundColor = color;
		refresh();
	}


	inline void IWindow::backgroundColor(float r, float g, float b)
	{
		pBackgroundColor.r = r;
		pBackgroundColor.g = g;
		pBackgroundColor.b = b;
		refresh();
	}




} // namespace Window
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


#endif // __YUNI_UI_LOCAL_WINDOW_WINDOW_HXX__
