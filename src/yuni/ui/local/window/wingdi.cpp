
#include "wingdi.h"
#include "../../../core/math.h"

#ifdef YUNI_WINDOWSYSTEM_MSW

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


	WinGDI* WinGDI::findWindow(HWND handle)
	{
		WindowList::iterator it;
		for (it = sWindowList.begin(); it != sWindowList.end(); ++it)
		{
			if (handle == it->first)
				return it->second;
		}
		return NULL;
	}


	void WinGDI::registerWindow(HWND handle, WinGDI* window)
	{
		if (!window)
			return;
		// If handle is already in the list, it will be overwritten
		sWindowList[handle] = window;
	}


	void WinGDI::unregisterWindow(HWND handle)
	{
		sWindowList.erase(handle);
	}


	LRESULT CALLBACK WinGDI::messageCallback(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WinGDI* window = findWindow(handle);
		assert(window != NULL && "Window was not properly registered !");
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
			case WM_QUIT: // Did we receive a Quit message?
			{
				unregisterWindow(handle);
				DestroyWindow(handle);
				window->onClose();
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
				RECT clientRect;
				GetClientRect(handle, &clientRect);
				window->onResize(
					static_cast<float>(clientRect.right - clientRect.left),
					static_cast<float>(clientRect.bottom - clientRect.top));
				return 0;
			}
		}

		// Pass all unhandled messages to DefWindowProc
		return DefWindowProc(handle, uMsg, wParam, lParam);
	}



	bool WinGDI::initialize()
	{
		// Windows Class Structure
		WNDCLASSEX wc;
		// Window Extended Style
		DWORD dwExStyle;
		// Window Style
		DWORD dwStyle;
		// Grabs Rectangle Upper Left / Lower Right Values
		RECT windowRect;

		windowRect.left = (long)pLeft;
		windowRect.right = (long)pWidth;
		windowRect.top = (long)pTop;
		windowRect.bottom = (long)pHeight;

		wc.cbSize = sizeof(WNDCLASSEX);
		// Grab An Instance For Our Window
		pHInstance = GetModuleHandle(NULL);
		// Redraw On Size, And Own DC For Window.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		// WndProc Handles Messages
		wc.lpfnWndProc = &WinGDI::messageCallback;
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
			dmScreenSettings.dmPelsWidth = (DWORD)pWidth;
			// Selected Screen Height
			dmScreenSettings.dmPelsHeight = (DWORD)pHeight;
			// Selected Bits Per Pixel
			dmScreenSettings.dmBitsPerPel = 24;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Try To Set Selected Mode And Get Results.
			// NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				// If it fails, set windowed Mode
				pFullScreen = false;
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
			Traits::CString<String>::Perform(pCaption), // Title
			dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // Style
			(int)pLeft, (int)pTop, // Window Position
			windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
			NULL, NULL, pHInstance, NULL)))
			return false;

		registerWindow(pHWnd, this);

		return true;
	}


	void WinGDI::move(float left, float top)
	{
		pLeft = left;
		pTop = top;
		SetWindowPos(pHWnd, 0, (long)pLeft, (long)pTop, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}


	void WinGDI::moveRelative(float left, float top)
	{
		pLeft += left;
		pTop += top;
		SetWindowPos(pHWnd, 0, (long)pLeft, (long)pTop, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}


	void WinGDI::resize(float width, float height)
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

		pWidth = width;
		pHeight = height;
		SetWindowPos(pHWnd, 0, 0, 0, (long)pWidth + ptDiff.x, (long)pHeight + ptDiff.y, SWP_NOMOVE | SWP_NOZORDER);
	}


	void WinGDI::show()
	{
		// When showing a window for the first time, SHOWNORMAL must be used !
		ShowWindow(pHWnd, SW_SHOWNORMAL);
	}

	void WinGDI::hide()
	{
		ShowWindow(pHWnd, SW_HIDE);
	}


	void WinGDI::minimize()
	{
		ShowWindow(pHWnd, SW_MINIMIZE);
	}


	void WinGDI::maximize()
	{
		ShowWindow(pHWnd, SW_MAXIMIZE);
	}


	void WinGDI::restore()
	{
		ShowWindow(pHWnd, SW_SHOW);
	}


	void WinGDI::bringToFront()
	{
		SetWindowPos(pHWnd, pStayOnTop ? HWND_TOPMOST : HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}


	void WinGDI::sendToBack()
	{
		SetWindowPos(pHWnd, pStayOnTop ? HWND_NOTOPMOST : HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}


	bool WinGDI::pollEvents()
	{
		MSG message;
		// Loop until there is no message left in the queue
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			// Dispatch the message to the callback
			DispatchMessage(&message);
		}
		return true;
	}


	void WinGDI::doRefresh()
	{
		// Ask for refresh by invalidating the client area
		InvalidateRect(pHWnd, NULL, true);
	}


	void WinGDI::doUpdateCaption()
	{
		SetWindowText(pHWnd, Traits::CString<String>::Perform(pCaption));
	}


	void WinGDI::doUpdateStyle()
	{
		// TODO
	}


	void WinGDI::doUpdateStayOnTop()
	{
		SetWindowPos(pHWnd, pStayOnTop ? HWND_TOPMOST : HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}




} // namespace Window
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW
