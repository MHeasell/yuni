#ifndef __YUNI_PRIVATE_UI_LOCAL_X11_X11WINDOW_H__
# define __YUNI_PRIVATE_UI_LOCAL_X11_X11WINDOW_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_X11

#	include "x11yuni.h"
#	include "../window.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace X11
{


	/*!
	** \brief Specialized window implementation for GLX (OpenGL-X11)
	*/
	class X11Window: public IWindow
	{
	public:
		X11Window(const Yuni::UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			: IWindow(source, bitDepth, fullScreen)
		{}
		virtual ~X11Window() {}

		virtual bool initialize();

		virtual void close();

		virtual bool pollEvents();

	protected:
		virtual void onInternalTitleChangedWL();

	private:
		//! Connection to a X11 Server through TCP or DECnet communications protocols
		Display* pDisplay;
		int pScreen;
		::Window pWindow;
		XSetWindowAttributes pAttr;
		XWindowAttributes pWndAttr;
		XEvent pXEvent;

	}; // class X11Window



} // namespace X11
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_X11

#endif // __YUNI_PRIVATE_UI_LOCAL_X11_X11WINDOW_H__
