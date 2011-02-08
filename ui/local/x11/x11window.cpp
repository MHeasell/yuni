
#include "x11window.h"

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


namespace // anonymous
{

	Visual* findARGBVisual(Display* dpy, int screen, int& depth)
	{
		XRenderPictFormat* format;

		XVisualInfo tmplate;
		tmplate.screen = screen;
		tmplate.depth = 32;
		// Temprorarily removed, does not compile with a C++ compiler...
		//	tmplate.class = TrueColor;

		int	nvi;
		XVisualInfo* xvi = XGetVisualInfo (dpy, VisualScreenMask | VisualDepthMask | VisualClassMask, &tmplate, &nvi);
		if (!xvi)
			return 0;

		Visual* visual = 0;
		for (int i = 0; i < nvi; ++i)
		{
			format = XRenderFindVisualFormat(dpy, xvi[i].visual);
			if (format->type == PictTypeDirect && format->direct.alphaMask)
			{
				visual = xvi[i].visual;
				break;
			}
		}

		depth = xvi->depth;

		XFree(xvi);
		return visual;
	}

} // namespace anonymous



	bool X11Window::initialize()
	{
		// Connect to the X server to open the local display
		if (!(pDisplay = XOpenDisplay(NULL)))
			return false;

		int screen = DefaultScreen(pDisplay);
		int depth;
		Visual* visual = findARGBVisual(pDisplay, screen, depth);
		::Window root = DefaultRootWindow(pDisplay);

		pAttr.colormap = XCreateColormap(pDisplay, root, visual, AllocNone);
		pAttr.background_pixel = BlackPixel(pDisplay, screen);
		pAttr.border_pixel = BlackPixel(pDisplay, screen);
		pAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

		if (pFullScreen)
		{
			pAttr.override_redirect = True;
		}

		pWindow = XCreateWindow(pDisplay, root, 30, 30,
			(unsigned int)pUIWnd->width(), (unsigned int)pUIWnd->height(), 0,
			depth, CopyFromParent, visual,
			CWBackPixel | CWBorderPixel | CWColormap | CWEventMask, &pAttr);

		XMapWindow(pDisplay, pWindow);
		XStoreName(pDisplay, pWindow, Traits::CString<String>::Perform(pUIWnd->title()));

		XGetWindowAttributes(pDisplay, pWindow, &pWndAttr);
		return true;
	}


	void X11Window::close()
	{
		destroyBoundEvents();

		// Switch back to original desktop resolution if we were in fs
		XCloseDisplay(pDisplay);
		pDisplay = NULL;
	}


	bool X11Window::pollEvents()
	{
		if (!XPending(pDisplay))
			return false;

		// Event loop
		do
		{
			XNextEvent(pDisplay, &pXEvent);
			switch (pXEvent.type)
			{
				case Expose:
					break;

				case ConfigureNotify:
					{
						// Resize Only if our window-size changed
						if ((int)pUIWnd->width() != pXEvent.xconfigure.width
							|| (int)pUIWnd->height() != pXEvent.xconfigure.height)
							resize((float)pXEvent.xconfigure.width, (float)pXEvent.xconfigure.height);
						break;
					}

				case ButtonPress:
					// KeyPress
					break;

				case KeyPress:
					if (0)
					{/*
						if (XLookupKeysym(&pXEvent.xkey, 0) == XK_Escape)
						{
							done = True;
						}
						if (XLookupKeysym(&pXEvent.xkey,0) == XK_F1)
						{
							destroyWindow();
							fullscreen = !fullscreen;
							createWindow();
						}*/
					}
					break;
				case ClientMessage:
					{
						if (*XGetAtomName(pDisplay, pXEvent.xclient.message_type) == *"WM_PROTOCOLS")
						{
							window()->close();
						}
						break;
					}
				default:
					break;
			}
		} while (XPending(pDisplay) > 0);

		return true;
	}



} // namespace X11
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
