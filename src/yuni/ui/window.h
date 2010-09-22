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
		//! Smart pointer
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
		template<typename StringT>
		explicit Window(const StringT& title);

		/*!
		** \brief Constructor with dimensions
		*/
		template<typename StringT>
		Window(const StringT& title, unsigned int width, unsigned int height);

		/*!
		** \brief Constructor with start position coordinates
		*/
		template<typename StringT>
		Window(const StringT& title, unsigned int x, unsigned int y, unsigned int width,
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
		** \brief Is the window currently closing ?
		*/
		bool pClosing;


	}; // class Window






} // namespace UI
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_UI_WINDOW_H__
