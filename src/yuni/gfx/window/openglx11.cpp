
#include "../../yuni.h"

#ifdef YUNI_WINDOWSYSTEM_X11

# include "openglx11.h"


namespace Yuni
{
namespace Gfx3D
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
				YUNI_X11LIB_NONE
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

		pWindow = XCreateWindow(pDisplay, root, 30, 30, pWidth, pHeight,
			0, vinfo->depth, CopyFromParent, vinfo->visual,
			CWBackPixel | CWBorderPixel | CWColormap, &pAttr);

		XMapWindow(pDisplay, pWindow);
		XStoreName(pDisplay, pWindow, "VERY SIMPLE APPLICATION");

		pContext = glXCreateContext(pDisplay, vinfo, NULL, True);
		if (NULL == pContext)
		{
			std::cerr << "glXCreateContext failed" << std::endl;
			return false;
		}
		if (!glXMakeCurrent(pDisplay, pWindow, pContext))
		{
			std::cout << "glXMakeCurrent failed" << std::endl;
			return false;
		}
		resize(pWidth, pHeight);
		if (!OpenGL::initialize())
		{
			std::cout << "GL initialization failed" << std::endl;
			return false;
		}
		return true;
	}


	void OpenGLX11::close()
	{
		if (pContext)
		{
			if (!::glXMakeCurrent(pDisplay, YUNI_X11LIB_NONE, NULL))
			{
				printf("Could not release drawing context.\n");
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

		OpenGL::close();
	}

	void OpenGLX11::blit()
	{
		//XNextEvent(pDisplay, &xev);
		XGetWindowAttributes(pDisplay, pWindow, &pWndAttr);
		glXSwapBuffers(pDisplay, pWindow);
	}

	bool OpenGLX11::verticalSync() const
	{
		typedef int (*SwapGetIntervalProto)();
		SwapGetIntervalProto getSwapIntervalEXT = 0;

		String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("GLX_MESA_swap_control") != String::npos)
			getSwapIntervalEXT = (SwapGetIntervalProto)glXGetProcAddress((GLubyte*)"glXGetSwapIntervalMESA");;

		if (getSwapIntervalEXT)
			return getSwapIntervalEXT();
		// From what I read, default is false when no extension is present.
		return false;
	}

	bool OpenGLX11::verticalSync(bool active)
	{
		typedef int (*SwapIntervalProto)(int);
		SwapIntervalProto swapIntervalEXT = 0;

		String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("GLX_SGI_swap_control") != String::npos)
			swapIntervalEXT = (SwapIntervalProto)glXGetProcAddress((GLubyte*)"glXSwapIntervalSGI");
		else if (extensions.find("GLX_MESA_swap_control") != String::npos)
			swapIntervalEXT = (SwapIntervalProto)glXGetProcAddress((GLubyte*)"glXSwapIntervalMESA");

		if (swapIntervalEXT)
			return swapIntervalEXT(active ? 1 : 0);
		return false;
	}


} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_X11
