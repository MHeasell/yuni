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
		//! Default visual style
		static const unsigned int DefaultStyleSet = wsResizeable | wsMinimizable | wsMaximizable;


	public:
		//! The most suitable smartptr for the class
		typedef SmartPtr<IWindow, Policy::Ownership::ReferenceCounted>  Ptr;
		//! Map of windows, by ID
		typedef std::map<ID, IWindow::Ptr>  Map;


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

		/*!
		** \brief Initialize the window
		**
		** \returns False if the initialization failed, true if it worked
		*/
		virtual bool initialize() = 0;

		/*!
		** \brief Move the window to a new position
		**
		** \param left New coordinate of the left of the window
		** \param top New coordinate of the top of the window
		*/
		virtual void move(float left, float top) = 0;

		/*!
		** \brief Move the window relatively to its old position
		**
		** \param left How much to add to the left of the window
		** \param top How much to add to the top of the window
		*/
		virtual void moveRelative(float left, float top) = 0;

		/*!
		** \brief Resize the window to new dimensions
		**
		** \param width New width of the window
		** \param height New height of the window
		*/
		virtual void resize(float width, float height) = 0;

		//! Show the window
		virtual void show() = 0;

		//! Hide the window
		virtual void hide() = 0;

		//! Minimize the window
		virtual void minimize() = 0;

		//! Maximize the window
		virtual void maximize() = 0;

		//! Restore the window (from minimization or maximization)
		virtual void restore() = 0;

		//! Bring the window to front
		virtual void bringToFront() = 0;

		//! Send the window to back
		virtual void sendToBack() = 0;

		/*!
		** \brief Poll events for this window
		**
		** \returns True to continue, false if a quit event was caught
		*/
		virtual bool pollEvents() = 0;

		//! Refresh the window when possible
		void refresh();

		//! Refresh the window immediately. This method should be used with care
		void forceRefresh();

		//! \name User update management
		//@{
		void beginUpdate();
		void endUpdate();
		//@}


		//! \name Caption
		//@{
		template<class StringT> void caption(const StringT& newstring);
		const String& caption() const {return pCaption; }
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
		//! Called when the local window caught a minimize event
		void onMinimize();
		//! Called when the local window caught a maximize event
		void onMaximize();
		//! Called when the local window caught a restore event
		void onRestore();
		//! Called when the local window caught a show event
		void onShow();
		//! Called when the local window caught a hide event
		void onHide();
		//! Called when the local window caught a resize event
		void onResize(float width, float height);

		/*!
		** \brief Called when the local window caught a close event
		**
		** \internal canClose is true by default. The window will really be closed if equals to true
		*/
		void onCloseQuery(bool& canClose);
		void onClose();

		//! Do the actual modification of the caption, abstract
		virtual void doUpdateCaption() = 0;
		//! Do the actual modification of the style, abstract
		virtual void doUpdateStyle() = 0;
		//! Do the actual modification of the stay on top option, abstract
		virtual void doUpdateStayOnTop() = 0;
		//! Do the actual refresh of the window
		virtual void doRefresh() = 0;

	protected:
		//! Caption of the window
		String pCaption;
		//! Window visual style
		unsigned int pStyleSet;
		//! Left-mots coordinate
		float pLeft;
		//! Top-most coordinate
		float pTop;
		//! Width of the window
		float pWidth;
		//! Height of the window
		float pHeight;
		//! Should the window always stay on top ?
		bool pStayOnTop;
		//! Should the window be displayed in full screen ?
		bool pFullScreen;
		//! Background color
		Color pBackgroundColor;

		//! Count the number of updates happening, wait until it reaches 0 to refresh
		unsigned int pRefreshRefCount;

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


# include "window.hxx"


#endif // __YUNI_UI_LOCAL_WINDOW_WINDOW_H__
