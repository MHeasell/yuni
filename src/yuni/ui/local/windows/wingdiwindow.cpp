
#include "wingdiwindow.h"
#include "../../../core/string.h"
#include "../../../core/math.h"


# ifdef YUNI_WINDOWSYSTEM_MSW

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace Windows
{


	namespace
	{

		typedef std::map<HWND, IWinGDIWindow*> WindowList;

		// This list contains all MFC windows created
		WindowList sWindowList;

		IWinGDIWindow* GetWindow(HWND handle)
		{
			WindowList::iterator it;
			for (it = sWindowList.begin(); it != sWindowList.end(); ++it)
			{
				if (handle == it->first)
					return it->second;
			}
			return NULL;
		}

		void AddWindow(HWND handle, IWinGDIWindow* window)
		{
			if (!window)
				return;
			// If handle is already in the list, it will be overwritten
			sWindowList[handle] = window;
		}

		void RemoveWindow(HWND handle)
		{
			sWindowList.erase(handle);
		}


		/*!
		** \brief Callback method for windows events
		**
		** \param hWnd Handle for this window
		** \param uMsg Message
		** \param wParam Additional Message Information
		** \param lParam Additional Message Information
		*/
		LRESULT CALLBACK WindowMessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			IWinGDIWindow* window = GetWindow(hWnd);
			// Check for Windows messages
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

				case WM_CLOSE: // Did we receive a Close message?
					{
						if (window && !window->closing())
						{
							DestroyWindow(hWnd);
							window->window()->close();
						}
						return 0;
					}

				case WM_ERASEBKGND:
				 	return 0;

				case WM_PAINT:
					{
						window->refresh();
						return 0;
					}
				case WM_SIZE: // Resize the window
				case WM_SIZING: // Resizing the window
					{
						if (window)
						{
							RECT clientRect;
							GetClientRect(hWnd, &clientRect);
							window->window()->resize(
								static_cast<float>(clientRect.right - clientRect.left),
								static_cast<float>(clientRect.bottom - clientRect.top));
// 							window->window()->resize(LOWORD(lParam), HIWORD(lParam));
						}
						return 0;
					}
			}

			// Pass all unhandled messages to DefWindowProc
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}


	} // anonymous namespace




	bool IWinGDIWindow::initialize()
	{
		// Windows Class Structure
		WNDCLASSEX wc;
		// Window Extended Style
		DWORD dwExStyle;
		// Window Style
		DWORD dwStyle;
		// Grabs Rectangle Upper Left / Lower Right Values
		RECT windowRect;

		windowRect.left = (long)pUIWnd->x();
		windowRect.right = (long)pUIWnd->width();
		windowRect.top = (long)pUIWnd->y();
		windowRect.bottom = (long)pUIWnd->height();

		wc.cbSize = sizeof(WNDCLASSEX);
		// Grab An Instance For Our Window
		pHInstance = GetModuleHandle(NULL);
		// Redraw On Size, And Own DC For Window.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		// WndProc Handles Messages
		wc.lpfnWndProc = (WNDPROC)WindowMessageCallback;
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
		// Load the small icon
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		// No Background Required
		wc.hbrBackground = NULL;
		// We Don't Want A Menu
		wc.lpszMenuName = NULL;
		// Set The Class Name
		wc.lpszClassName = Traits::CString<String>::Perform(pWindowClassName);

		// Attempt To Register The Window Class
		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Failed to register the Window Class.", "Window Creation Error", MB_OK | MB_ICONEXCLAMATION);
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
			dmScreenSettings.dmPelsWidth = (DWORD)pUIWnd->width();
			// Selected Screen Height
			dmScreenSettings.dmPelsHeight = (DWORD)pUIWnd->height();
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
					Traits::CString<String>::Perform(pUIWnd->title()), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					// Set windowed Mode
					pFullScreen = false;
				else
				{
					// Pop Up A Message Box Letting User Know The Program Is Closing.
					MessageBox(NULL, "Program will now close.","Window Creation Error", MB_OK | MB_ICONSTOP);
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
			dwExStyle = WS_EX_APPWINDOW; // | WS_EX_WINDOWEDGE;
			// Windows Style
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		// Adjust window to true requested size
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

		// Create The Window
		if (!(pHWnd = CreateWindowEx(dwExStyle,
			Traits::CString<String>::Perform(pWindowClassName), // Class name
			Traits::CString<String>::Perform(pUIWnd->title()), // Title
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // Style
			(int)pUIWnd->x(), (int)pUIWnd->y(), // Window Position
			windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, pHInstance, NULL)))
		{
			// Reset The Display
			pUIWnd->close();
			MessageBox(NULL, "CreateWindowEx call failed.", "Window Creation Error", MB_OK | MB_ICONEXCLAMATION);
			return false;
		}

		ShowWindow(pHWnd, pFullScreen ? SW_MAXIMIZE : SW_SHOWNORMAL);

		AddWindow(pHWnd, this);

		return true;
	}


	void IWinGDIWindow::resize(float width, float height)
	{
		RECT clientRect;
		GetClientRect(pHWnd, &clientRect);
		// Do nothing if sizes did not change
		if (Yuni::Math::Equals(width, (float)(clientRect.right - clientRect.left)) &&
			Yuni::Math::Equals(height, (float)(clientRect.top - clientRect.bottom)))
			return;

		RECT fullRect;
		GetWindowRect(pHWnd, &fullRect);
		// The size modifications are only applied to the client size, so take into account
		// the size of the whole window (with title bar, status bar, scrollbars, ...)
		POINT ptDiff;
		ptDiff.x = (fullRect.right - fullRect.left) - clientRect.right;
		ptDiff.y = (fullRect.bottom - fullRect.top) - clientRect.bottom;
		MoveWindow(pHWnd, fullRect.left, fullRect.top, (long)width + ptDiff.x, (long)height + ptDiff.y, TRUE);
	}


	void IWinGDIWindow::close()
	{
		if (!pUIWnd)
			// Already destroyed
			return;

		// Inform the UI::Window. It might already know but it won't hurt.
		pUIWnd->close();
		// Break the link to UI::Window
		pUIWnd = nullptr;

		destroyBoundEvents();

		// Are We In Fullscreen Mode?
		if (pFullScreen)
		{
			// If So Switch Back To The Desktop
			ChangeDisplaySettings(NULL, 0);
			// Show Mouse Pointer
			ShowCursor(true);
		}

		// Remove the window from the static list
		RemoveWindow(pHWnd);
		if (sWindowList.empty())
			PostQuitMessage(0); // Send a Quit message

		// Are We Able To Destroy The Window?
		if (pHWnd && !DestroyWindow(pHWnd))
		{
			MessageBox(NULL, "Could Not Release HWINDOW.", "Shutdown Error", MB_OK | MB_ICONINFORMATION);
			pHWnd = NULL;
		}

		// Are We Able To Unregister Class
		if (!UnregisterClass(Traits::CString<String>::Perform(pWindowClassName), pHInstance))
		{
			MessageBox(NULL, "Could Not Unregister Class.", "Shutdown Error", MB_OK | MB_ICONINFORMATION);
			pHInstance = NULL;
		}
	}

	bool IWinGDIWindow::pollEvents()
	{
		const int THRESHOLD = 100;
		static int current = 0;
		MSG msg;
		bool msgProcessed = false;

		if (current > THRESHOLD)
			current = 0;
		else
		{
			current++;
			return false;
		}

		// Is there a message waiting?
		if (!closing() && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Have we received a Quit message?
			if (msg.message == WM_QUIT)
			{
				if (!closing())
					pUIWnd->close();
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



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

# endif // YUNI_WINDOWSYSTEM_MSW
