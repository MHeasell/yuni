#ifndef __YUNI_UI_LOCAL_WINDOW_WINGDI_H__
# define __YUNI_UI_LOCAL_WINDOW_WINGDI_H__

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
namespace Window
{


	/*!
	** \brief Implementation of a window for Microsoft Windows GDI+
	*/
	class WinGDI: public IWindow
	{
	public:
		//! \name Constructor & Destructor
		//@{
		WinGDI()
		{}
		//! Destructor
		virtual ~WinGDI() {}
		//@}

		virtual bool initialize();

		virtual void move(float left, float top);
		virtual void moveRelative(float left, float top);

		virtual void resize(float width, float height);

		virtual void show();

		virtual void hide();

		virtual void minimize();

		virtual void maximize();

		virtual void restore();

		virtual void bringToFront();

		virtual void sendToBack();

		virtual bool pollEvents();


	protected:
		//! Do the actual modification of the caption, virtual, called from base
		virtual void doUpdateCaption();

		//! Do the actual modification of the style, virtual, called from base
		virtual void doUpdateStyle();

		//! Do the actual modification of the stay on top option, virtual, called from base
		virtual void doUpdateStayOnTop();

		//! Do the actual refresh of the window
		virtual void doRefresh();


	protected:
		//! MS Windows sorts its windows by "class"
		String pWindowClassName;

		//! Instance handle
		HINSTANCE pHInstance;

		//! Window handle
		HWND pHWnd;

	}; // class WinGDI




} // namespace Window
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_UI_LOCAL_WINDOW_WINGDI_H__
