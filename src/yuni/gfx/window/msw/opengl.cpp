
#include "../msw/opengl.h"
#include "../../api/gl.h"
#include "../../../core/string.h"



# ifdef YUNI_WINDOWSYSTEM_MSW

namespace Yuni
{
namespace Gfx
{
namespace Window
{

	bool OpenGLMSW::initialize()
	{
		if (!AMSWindows::initialize())
			return false;

		// Did We Get A Device Context?
		if (!(pHDC = GetDC(pHWnd)))
		{
			close();
			MessageBox(NULL, "Can't create a GL device context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		static PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof (PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, pBitDepth, 0, 0, 0, 0, 0, 0,	// Color Bits Ignored
				// No Alpha Buffer
				0,
				// Shift Bit Ignored
				0,
				// No Accumulation Buffer
				0,
				// Accumulation Bits Ignored
				0, 0, 0, 0,
				// 16Bit Z-Buffer (Depth Buffer)
				16,
				// No Stencil Buffer
				0,
				// No Auxiliary Buffer
				0,
				// Main Drawing Layer
				PFD_MAIN_PLANE,
				// Reserved
				0,
				// Layer Masks Ignored
				0, 0, 0
			};

		unsigned int pixelFormat;
		// Did Windows find a matching pixel format?
		if (!(pixelFormat = ChoosePixelFormat(pHDC, &pfd)))
		{
			close();
			MessageBox(NULL, "Can't find a suitable PixelFormat.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Are We Able To Set The Pixel Format?
		if (!SetPixelFormat(pHDC, pixelFormat, &pfd))
		{
			close();
			MessageBox(NULL, "Can't set the PixelFormat.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Are We Able To Get A Rendering Context?
		if (!(pHRC = wglCreateContext(pHDC)))
		{
			close();
			MessageBox(NULL, "Can't create a GL rendering context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Try To Activate The Rendering Context
		if (!wglMakeCurrent(pHDC, pHRC))
		{
			close();
			MessageBox(NULL, "Can't activate the GL Rendering Context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Show the window
		ShowWindow(pHWnd, SW_SHOW);
		// Slightly higher priority
		SetForegroundWindow(pHWnd);
		// Sets keyboard focus to the window
		SetFocus(pHWnd);

		// Set up our perspective GL screen
		resize(pWidth, pHeight);

		// Initialize our newly created GL window
		if (!OpenGL::initialize())
		{
			close();
			MessageBox(NULL, "Initialization failed.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		return true;
	}


	void OpenGLMSW::close()
	{
		// Do We Have A Rendering Context?
		if (pHRC)
		{
			// Are We Able To Release The DC And RC Contexts?
			if (!wglMakeCurrent(NULL, NULL))
				MessageBox(NULL, "Release of DC and RC failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

			// Are We Able To Delete The RC?
			if (!wglDeleteContext(pHRC))
				MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			pHRC = NULL;
		}

		// Are We Able To Release The DC?
		if (pHDC && !ReleaseDC(pHWnd, pHDC))
		{
			MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			pHDC = NULL;
		}

		AMSWindows::close();
		OpenGL::release();
	}


	void OpenGLMSW::resize(unsigned int width, unsigned int height)
	{
		OpenGL::resize(width, height);
		AWindow::resize(width, height);
	}


	bool OpenGLMSW::verticalSync() const
	{
		typedef BOOL (APIENTRY *SwapGetIntervalProto)();
		SwapGetIntervalProto getSwapIntervalEXT = 0;

		const String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("WGL_EXT_swap_control") != String::npos)
		{
			getSwapIntervalEXT = (SwapGetIntervalProto)wglGetProcAddress("wglGetSwapIntervalEXT");;
			if (getSwapIntervalEXT)
				return getSwapIntervalEXT() ? true : false;
		}
		// From experience, default seems to be true under windows
		return true;
	}


	bool OpenGLMSW::verticalSync(bool active)
	{
		typedef BOOL (APIENTRY *SwapIntervalProto)(int);
		SwapIntervalProto swapIntervalEXT = 0;

		const String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("WGL_EXT_swap_control") != String::npos)
		{
			swapIntervalEXT = (SwapIntervalProto)wglGetProcAddress("wglSwapIntervalEXT");
			if (swapIntervalEXT)
				return swapIntervalEXT(active ? 1 : 0) ? true : false;
		}
		// Fail
		return false;
	}


	void OpenGLMSW::onBlitWL()
	{
		SwapBuffers(pHDC);
	}



} // namespace Window
} // namespace Gfx
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_MSW
