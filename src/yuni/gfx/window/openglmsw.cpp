
#include "openglmsw.h"
#include "factory.h"
#include "../../private/gfx3d/gl/gl.h"
#include "../../core/string.h"

# ifdef YUNI_WINDOWSYSTEM_MSW

namespace Yuni
{
namespace Gfx3D
{
namespace Window
{


	namespace
	{
		AWindow* sWindow = NULL;


		/*!
		** \brief Callback method for windows events
		**
		** \param hWnd Handle for this window
		** \param uMsg Message
		** \param wParam Additional Message Information
		** \param lParam Additional Message Information
		*/
		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			// Check For Windows Messages
			switch (uMsg)
			{
				case WM_SYSCOMMAND:
					{
						switch (wParam)
						{
							case SC_SCREENSAVE:
							case SC_MONITORPOWER:
								return 0;
						}
						break;
					}

				case WM_CLOSE: // Did We Receive A Close Message?
					{
						PostQuitMessage(0); // Send A Quit Message
						if (sWindow && !sWindow->closing())
							sWindow->onClose();
						return 0;
					}

				case WM_SIZE: // Resize The OpenGL Window
					{
						if (sWindow)
							sWindow->resize(LOWORD(lParam), HIWORD(lParam));
						return 0;
					}
			}

			// Pass All Unhandled Messages To DefWindowProc
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

	} // anonymous namespace


	bool OpenGLMSW::initialize()
	{
		// Holds The Results After Searching For A Match
		unsigned int pixelFormat;
		// Windows Class Structure
		WNDCLASS wc;
		// Window Extended Style
		DWORD dwExStyle;
		// Window Style
		DWORD dwStyle;
		// Grabs Rectangle Upper Left / Lower Right Values
		RECT windowRect;

		windowRect.left = 0;
		windowRect.right = (long) pWidth;
		windowRect.top = 0;
		windowRect.bottom = (long) pHeight;

		// Grab An Instance For Our Window
		pHInstance = GetModuleHandle(NULL);
		// Redraw On Size, And Own DC For Window.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		// WndProc Handles Messages
		wc.lpfnWndProc = (WNDPROC)WndProc;
		// No Extra Window Data
		wc.cbClsExtra = 0;
		// No Extra Window Data
		wc.cbWndExtra = 0;
		// Set The Instance
		wc.hInstance = pHInstance;
		// Load The Default Icon
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		// Load The Arrow Pointer
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		// No Background Required For GL
		wc.hbrBackground = NULL;
		// We Don't Want A Menu
		wc.lpszMenuName = NULL;
		// Set The Class Name
		wc.lpszClassName = "OpenGL";

		// Attempt To Register The Window Class
		if (!RegisterClass(&wc))
		{
			MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Attempt Fullscreen Mode?
		if (pFullScreen)
		{
			// Device Mode
			DEVMODE dmScreenSettings;
			// Makes Sure Memory's Cleared
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			// Size Of The Devmode Structure
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			// Selected Screen Width
			dmScreenSettings.dmPelsWidth = pWidth;
			// Selected Screen Height
			dmScreenSettings.dmPelsHeight = pHeight;
			// Selected Bits Per Pixel
			dmScreenSettings.dmBitsPerPel = pBitDepth;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Try To Set Selected Mode And Get Results.
			// NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				// If The Mode Fails, Offer Two Options:
				// Quit Or Use Windowed Mode.
				if (MessageBox(NULL, "The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?",
					String::CString(pTitle), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					// Set windowed Mode
					pFullScreen = false;
				else
				{
					// Pop Up A Message Box Letting User Know The Program Is Closing.
					MessageBox(NULL, "Program will now close.","GL Initialization Error", MB_OK | MB_ICONSTOP);
					return false;
				}
			}
		}

		// Are We Still In Fullscreen Mode?
		if (pFullScreen)
		{
			// Window Extended Style
			dwExStyle = WS_EX_APPWINDOW;
			// Windows Style
			dwStyle = WS_POPUP;
			// Hide Mouse Pointer
			ShowCursor(FALSE);
		}
		else
		{
			// Window Extended Style
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			// Windows Style
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		// Adjust window to true requested size
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

		// Create The Window
		if (!(pHWnd = CreateWindowEx(dwExStyle, "OpenGL", String::CString(pTitle),
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, // Window Position
			windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, pHInstance, NULL)))
		{
			// Reset The Display
			close();
			MessageBox(NULL, "Window creation error.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
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

		// Did We Get A Device Context?
		if (!(pHDC = GetDC(pHWnd)))
		{
			close();
			MessageBox(NULL, "Can't create a GL device context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

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
			MessageBox(NULL, "Can't create A GL rendering context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// Try To Activate The Rendering Context
		if (!wglMakeCurrent(pHDC, pHRC))
		{
			close();
			MessageBox(NULL, "Can't Activate The GL Rendering Context.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
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
			MessageBox(NULL, "Initialization Failed.", "GL Initialization Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		// This is an hideous hack to be able to access the window when in the WndProc callback
		// This will _not_ work with multiple windows
		if (NULL == sWindow)
			sWindow = const_cast<OpenGLMSW*>(this);
		return true;
	}


	void OpenGLMSW::close()
	{
		// Are We In Fullscreen Mode?
		if (pFullScreen)
		{
			// If So Switch Back To The Desktop
			ChangeDisplaySettings(NULL, 0);
			// Show Mouse Pointer
			ShowCursor(true);
		}

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

		// Are We Able To Destroy The Window?
		if (pHWnd && !DestroyWindow(pHWnd))
		{
			MessageBox(NULL, "Could Not Release HWINDOW.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			pHWnd = NULL;
		}

		// Are We Able To Unregister Class
		if (!UnregisterClass("OpenGL", pHInstance))
		{
			MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
			pHInstance = NULL;
		}

		OpenGL::close();
	}

	bool OpenGLMSW::verticalSync() const
	{
		typedef BOOL (APIENTRY *SwapGetIntervalProto)();
		SwapGetIntervalProto getSwapIntervalEXT = 0;

		String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("WGL_EXT_swap_control") != String::npos)
			getSwapIntervalEXT = (SwapGetIntervalProto)wglGetProcAddress("wglGetSwapIntervalEXT");;

		if (getSwapIntervalEXT)
			return getSwapIntervalEXT();
		// From experience, default seems to be true under windows
		return true;
	}

	bool OpenGLMSW::verticalSync(bool active)
	{
		typedef BOOL (APIENTRY *SwapIntervalProto)(int);
		SwapIntervalProto swapIntervalEXT = 0;

		String extensions((const char*)glGetString(GL_EXTENSIONS));
		if (extensions.find("WGL_EXT_swap_control") != String::npos)
			swapIntervalEXT = (SwapIntervalProto)wglGetProcAddress("wglSwapIntervalEXT");

		if (swapIntervalEXT)
			return swapIntervalEXT(active ? 1 : 0);
		return false;
	}

	bool OpenGLMSW::pollEvents()
	{
		MSG msg;
		bool msgProcessed = false;

		// Is there a message waiting?
		while (!closing() && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Have we received a Quit message?
			if (msg.message == WM_QUIT)
			{
				onClose();
			}
			// If not, deal with window messages
			else
			{
				// Translate The Message
				TranslateMessage(&msg);
				// Dispatch The Message
				DispatchMessage(&msg);
			}
			msgProcessed = true;
		}
		return msgProcessed;
	}

	void OpenGLMSW::onTitleChanged()
	{
		SetWindowText(pHWnd, String::CString(pTitle));
	}

} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_MSW
