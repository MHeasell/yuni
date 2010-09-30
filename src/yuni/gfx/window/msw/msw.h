#ifndef __YUNI_GFX_WINDOW_MSWINDOWS_H__
# define __YUNI_GFX_WINDOW_MSWINDOWS_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../../core/system/windows.hdr.h"
#	include "../window.h"



namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Abstract implementation of a window for Microsoft Windows
	**
	** Inherited classes: OpenGLMSW and DirectXMSW
	*/
	class IMSWindows: public IWindow
	{
	public:
		//! The Threading Policy
		typedef IWindow::ThreadingPolicy ThreadingPolicy;

	public:
		IMSWindows(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			:IWindow(source, bitDepth, fullScreen)
		{}
		virtual ~IMSWindows() {}

		virtual bool initialize();

		virtual void close();

		virtual bool pollEvents();

	protected:
		virtual void onInternalTitleChangedWL();

	protected:
		String pWindowClassName;
		HINSTANCE pHInstance;
		HWND pHWnd;

	}; // class IMSWindows



} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_MSWINDOWS_H__
