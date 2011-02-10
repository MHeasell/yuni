#ifndef __YUNI_UI_LOCAL_WINDOW_WINGDIWINDOW_H__
# define __YUNI_UI_LOCAL_WINDOW_WINGDIWINDOW_H__

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
	class WinGDIWindow: public IWindow
	{
	public:
		//! \name Constructor & Destructor
		//@{
		WinGDIWindow()
		{}
		//! Destructor
		virtual ~WinGDIWindow() {}
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

		virtual bool pollEvents();

		virtual void refresh();

		//! \name Caption
		//@{
		template<class StringT> void caption(const StringT& newstring);
		const String& caption() const;
		//@}

		//! \name Window Style
		//@{
		void style(unsigned int flags);
		unsigned int style() const {return pStyleSet;}
		//@}

		//! \name Stay on Top
		//@{
		virtual void stayOnTop(bool alwaysOnTop);
		bool stayOnTop() const {return pStayOnTop;}
		//@}

		//! \name Colors
		//@{
		void backgroundColor(const Color& color);
		void backgroundColor(float r, float g, float b);
		const Color& backgroundColor() const {return pBackgroundColor;}
		//@}


	protected:
		//! MS Windows sorts its windows by "class"
		String pWindowClassName;

		//! Instance handle
		HINSTANCE pHInstance;

		//! Window handle
		HWND pHWnd;

	}; // class WinGDIWindow




} // namespace Window
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_UI_LOCAL_WINDOW_WINGDIWINDOW_H__
