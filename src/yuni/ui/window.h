#ifndef __YUNI_UI_WINDOW_H__
# define __YUNI_UI_WINDOW_H__

# include "../yuni.h"
# include "../core/string.h"
# include "../core/event/event.h"
# include "component.h"


namespace Yuni
{
namespace UI
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class Window: public IComponent
	{
	public:
		//! Window vector
		typedef std::vector<Window> Vector;


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Short constructor
		*/
		template<typename StringT>
		Window(const StringT& title);

		/*!
		** \brief Constructor with dimensions
		*/
		template<typename StringT>
		Window(const StringT& title, unsigned int width, unsigned int height);

		/*!
		** \brief Constructor with start position coordinates
		*/
		template<typename StringT, typename NumberT, typename NumberT2>
		Window(const StringT& title, NumberT x, NumberT2 y, unsigned int width,
			unsigned int height);

		/*!
		** \brief Constructor with start position as a point
		*/
		template<typename StringT, typename NumberT>
		Window(const StringT& title, const Point2D<NumberT>& pos, unsigned int width,
			unsigned int height);

		//! Virtual destructor
		virtual ~Window();
		//@}


		//! \name Methods
		//@{
		/*!
		** \brief Init the window
		**
		** This is implementation-dependent.
		*/
		virtual bool initialize() = 0;

		/*!
		** \brief Close the window, release everything
		**
		** This is implementation-dependent
		*/
		virtual void close();

		/*!
		** \brief Get whether the window is in the process of closing
		*/
		bool closing() const;

		/*!
		** \brief Inform the component that other representations are up to date
		**
		** Once an internal representation of the component has been updated,
		** the component should not be marked "modified" anymore.
		**
		** A clever trick will be required on call to avoid losing modifications
		** due to multiple threads updating the status.
		*/
		virtual void synchronized()
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pModified = false;
			pTitleModified = false;
		}
		//@}


		//! \name Title of the Window
		//@{
		//! Get the Title of the window
		const String& title() const { return pTitle; }

		//! Set the title of the window
		template<typename StringT>
		void title(const StringT& newTitle);
		//@}


		//! \name Events
		//@{
		/*!
		** \brief Read the events in queue and launch the various handlers
		** \return True if events were processed, False otherwise
		*/
		virtual bool pollEvents() { return false; }

		virtual void onClose() { pClosing = true; }

	public:
		Event<void (float /* x */, float /* y */)> onMouseDown;
		Event<void (float /* x */, float /* y */)> onMouseClick;
		Event<void (float /* x */, float /* y */)> onMouseUp;
		Event<void (float /* x */, float /* y */, float /* delta */)> onMouseWheel;

		Event<void (unsigned char /* key */)> onKeyDown;
		Event<void (unsigned char /* key */)> onKeyPressed;
		Event<void (unsigned char /* key */)> onKeyUp;

		//@}

	protected:

		/*!
		** \brief Title of the window
		*/
		String pTitle;

		/*!
		** \brief Store if the title has changed
		*/
		bool pTitleModified;

		/*!
		** \brief Is the window currently closing ?
		*/
		bool pClosing;


	}; // class Window



} // namespace UI
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_UI_WINDOW_H__
