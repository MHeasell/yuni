
#include "../../../yuni.h"

#ifdef YUNI_WINDOWSYSTEM_X11

# include "../x11/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	bool OpenGLX11::initialize()
	{
		// Connect to the X server to open the local display
		if (!(pDisplay = XOpenDisplay(NULL)))
			return false;

		// Attributes
		int attributes[] =
			{
				GLX_RGBA,
				GLX_DEPTH_SIZE, 24,
				GLX_STENCIL_SIZE, 8,
				GLX_ALPHA_SIZE, 8,
				GLX_DOUBLEBUFFER,
				YUNI_X11LIB_NONE // end of list
			};
		XVisualInfo* vinfo = glXChooseVisual(pDisplay, DefaultScreen(pDisplay), attributes);
		if (NULL == vinfo)
		{
			std::cerr << "ERROR: Cannot open window" << std::endl;
			return false;
		}
		::Window root = DefaultRootWindow(pDisplay);

		pAttr.colormap = XCreateColormap(pDisplay, root, vinfo->visual, AllocNone);
		pAttr.background_pixel = BlackPixel(pDisplay, vinfo->screen);
		pAttr.border_pixel = BlackPixel(pDisplay, vinfo->screen);
		pAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

		if (pFullScreen)
		{
			pAttr.override_redirect = True;
		}

		pWindow = XCreateWindow(pDisplay, root, 30, 30,
			(unsigned int)pUIWnd->width(), (unsigned int)pUIWnd->height(), 0,
			vinfo->depth, CopyFromParent, vinfo->visual,
			CWBackPixel | CWBorderPixel | CWColormap | CWEventMask, &pAttr);

		XMapWindow(pDisplay, pWindow);
		XStoreName(pDisplay, pWindow, String::CString(pUIWnd->title()));

		pContext = ::glXCreateContext(pDisplay, vinfo, NULL, True);
		if (NULL == pContext)
		{
			std::cerr << "glXCreateContext failed" << std::endl;
			return false;
		}

				if (!glXMakeCurrent(pDisplay, pWindow, pContext))
		{
			std::cerr << "DRI not available" << std::endl;
			return false;
		}
		resize(pUIWnd->width(), pUIWnd->height());
		if (!Surface::OpenGL::initialize())
		{
			std::cerr << "GL initialization failed" << std::endl;
			return false;
		}
		// Window Attributes
		XGetWindowAttributes(pDisplay, pWindow, &pWndAttr);
		return true;
	}


	void OpenGLX11::close()
	{
		destroyBoundEvents();

		if (pContext)
		{
			if (!::glXMakeCurrent(pDisplay, YUNI_X11LIB_NONE, NULL))
			{
				std::cerr << "Could not release drawing context.\n";
			}
			glXDestroyContext(pDisplay, pContext);
			pContext = NULL;
		}
		// Switch back to original desktop resolution if we were in fs
		if (pFullScreen)
		{
//			XF86VidModeSwitchToMode(pDisplay, pScreen, &GLWin.deskMode);
//			XF86VidModeSetViewPort(pDisplay, pScreen, 0, 0);
		}
		XCloseDisplay(pDisplay);
		pDisplay = NULL;

		Surface::OpenGL::release();
	}


	void OpenGLX11::blitWL()
	{
	//	XGetWindowAttributes(pDisplay, pWindow, &pWndAttr);
		// Swap buffer when doublebuffer is enabled
		::glXSwapBuffers(pDisplay, pWindow);
	}


	bool OpenGLX11::verticalSync() const
	{
		typedef int (*SwapGetIntervalProto)();
		SwapGetIntervalProto getSwapIntervalEXT = 0;

		const String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("GLX_MESA_swap_control") != String::npos)
		{
			getSwapIntervalEXT = (SwapGetIntervalProto)glXGetProcAddress((const GLubyte*)"glXGetSwapIntervalMESA");
			if (getSwapIntervalEXT)
				return getSwapIntervalEXT();
		}
		// From what I read, default is false when no extension is present.
		return false;
	}


	bool OpenGLX11::verticalSync(bool active)
	{
		typedef int (*SwapIntervalProto)(int);
		SwapIntervalProto swapIntervalEXT = 0;

		const String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("GLX_SGI_swap_control") != String::npos)
			swapIntervalEXT = (SwapIntervalProto)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
		else
		{
			if (extensions.find("GLX_MESA_swap_control") != String::npos)
				swapIntervalEXT = (SwapIntervalProto)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
		}
		if (swapIntervalEXT)
			return swapIntervalEXT(active ? 1 : 0);
		return false;
	}


	void OpenGLX11::onInternalTitleChangedWL()
	{
		// The title of the window has been changed - Notifying the XWindow
		XTextProperty text;
		char* t = const_cast<char*>(String::CString(pUIWnd->title()));
		XStringListToTextProperty(&t, 1, &text);
		XSetWMName(pDisplay, pWindow, &text);
	}



} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_X11
