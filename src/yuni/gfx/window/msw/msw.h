#ifndef __YUNI_GFX_WINDOW_MSWINDOWS_H__
# define __YUNI_GFX_WINDOW_MSWINDOWS_H__

# include <list>
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
		IMSWindows(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:IWindow(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize();
		virtual void close();

		virtual bool pollEvents();

	protected:
		virtual void onInternalTitleChangedWL();

	protected:
		String pWindowClassName;
		HINSTANCE pHInstance;
		HWND pHWnd;

	}; // class AMSWindows



} // namespace Window
} // namespace Gfx3D
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_MSWINDOWS_H__
