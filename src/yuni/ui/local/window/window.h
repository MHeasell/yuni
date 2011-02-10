#ifndef __YUNI_UI_LOCAL_WINDOW_WINDOW_H__
# define __YUNI_UI_LOCAL_WINDOW_WINDOW_H__

# include "../../../yuni.h"
# include "types.h"


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
	//! Unique numeric Identifier
	typedef unsigned int ID;


	/*!
	**
	** \internal All those methods are **not** thread-safe, because called from
	**   the main thread (see QueueService)
	*/
	class IWindow
	{
	public:
		//! The most suitable smartptr for the class
		typedef SmartPtr<IWindow, Policy::Ownership::ReferenceCounted>  Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		IWindow();
		//! Destructor
		virtual ~IWindow();
		//@}

		virtual bool initialize() = 0;

		virtual void move(float x, float y) = 0;
		virtual void moveRelative(float x, float y) = 0;

		virtual void resize(float width, float height) = 0;

		virtual void show() = 0;

		virtual void hide() = 0;

		virtual void minimize() = 0;

		virtual void maximize() = 0;

		virtual void restore() = 0;

		virtual bool pollEvents() = 0;

		virtual void refresh() = 0;


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
		void onMinimize();
		void onMaximize();
		void onShow();
		/*!
		** \internal canClose is true by default. The window will really be closed if equals to true
		*/
		void onCloseQuery(bool& canClose);
		void onClose();

	protected:
		//! Caption of the window
		String pCaption;
		unsigned int pStyleSet;
		float pLeft;
		float pTop;
		float pWidth;
		float pHeight;
		bool pStayOnTop;
		Color pBackgroundColor;

	}; // class IWindow




	//! Map of local Windows
	typedef std::map<ID, IWindow::Ptr> Map;
	//! Windows smartptr
	typedef IWindow::Ptr  Ptr;



} // namespace Window
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_UI_LOCAL_WINDOW_WINDOW_H__
