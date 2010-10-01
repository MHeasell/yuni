#ifndef __YUNI_UI_WINDOW_H__
# define __YUNI_UI_WINDOW_H__

# include "../yuni.h"
# include "../core/string.h"
# include "../core/event/event.h"
# include "../thread/policy.h"
# include "controlcontainer.h"


namespace Yuni
{
namespace UI
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class Window: public IControlContainer
	{
	public:
		//! Smart pointer, inherited from the ancestor
		typedef IComponent::SmartPtrInfo<Window>::Type Ptr;
		//! Vector of controls
		typedef std::vector<Ptr> Vector;

		//! Threading Policy
		typedef IComponent::ThreadingPolicy ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Short constructor
		*/
		template<class StringT>
		explicit Window(const StringT& title);

		/*!
		** \brief Constructor with dimensions
		*/
		template<class StringT>
		Window(const StringT& title, float width, float height);

		/*!
		** \brief Constructor with start position coordinates
		*/
		template<class StringT>
		Window(const StringT& title, float x, float y, float width, float height);

		/*!
		** \brief Constructor with start position as a point
		*/
		template<class StringT, class T>
		Window(const StringT& title, const Point2D<T>& pos, float width, float height);

		//! Virtual destructor
		virtual ~Window();
		//@}


		//! \name Methods
		//@{
		/*!
		** \brief Close the window, release everything
		*/
		void close();

		/*!
		** \brief Get whether the window is in the process of closing
		*/
		bool closing() const;
		//@}


		//! \name Title of the Window
		//@{
		//! Get the Title of the window
		String title() const;
		//! Set the title of the window
		template<class StringT> void title(const StringT& newTitle);
		//@}


		//! \name Events
		//@{
		/*!
		** \brief Read the events in queue and launch the various handlers
		**
		** \return True if events were processed, False otherwise
		*/
		virtual bool pollEvents();

		//@}


	public:
		//! \name Events
		//@{
		Event<void ()> onClose;

		Event<void (float /* x */, float /* y */)> onMouseDown;
		Event<void (float /* x */, float /* y */)> onMouseClick;
		Event<void (float /* x */, float /* y */)> onMouseUp;
		Event<void (float /* x */, float /* y */, float /* delta */)> onMouseWheel;

		Event<void (unsigned char /* key */)> onKeyDown;
		Event<void (unsigned char /* key */)> onKeyPressed;
		Event<void (unsigned char /* key */)> onKeyUp;
		//@}

	protected:
		//! Set the title of the window (without lock)
		template<class StringT> void titleWL(const StringT& newTitle);

	private:
		//! Title of the window
		String pTitle;
		//! Is the window currently closing ?
		bool pClosing;

	}; // class Window






} // namespace UI
} // namespace Yuni


# include "window.hxx"


#endif // __YUNI_UI_WINDOW_H__
