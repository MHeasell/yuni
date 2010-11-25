#ifndef __YUNI_PRIVATE_UI_LOCAL_WINDOWS_WINGDIWINDOW_H__
# define __YUNI_PRIVATE_UI_LOCAL_WINDOWS_WINGDIWINDOW_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../../core/system/windows.hdr.h"
#	include "../window.h"



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


	/*!
	** \brief Abstract implementation of a window for Microsoft Windows GDI+
	*/
	class IWinGDIWindow: public IWindow
	{
	public:
		//! The Threading Policy
		typedef IWindow::ThreadingPolicy ThreadingPolicy;

	public:
		IWinGDIWindow(const Yuni::UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen)
			: IWindow(source, bitDepth, fullScreen)
		{}
		virtual ~IWinGDIWindow() {}

		virtual bool initialize();

		virtual void resize(float width, float height);

		virtual void close();

		virtual bool pollEvents();

	protected:
		//! Windows sorts its windows by "class"
		String pWindowClassName;

		//! Instance handle
		HINSTANCE pHInstance;

		//! Window handle
		HWND pHWnd;

	}; // class IWinGDIWindow



} // namespace Windows
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_PRIVATE_UI_LOCAL_WINDOWS_WINGDIWINDOW_H__
