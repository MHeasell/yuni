#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__

# include "../../yuni.h"
# include "component.h"
# include "desktop.h"
# include "../device.h"
# include "../../core/string.h"
# include "../../core/event/event.h"
# include "../surface/surface.h"


namespace Yuni
{

	// Forward declaration
	class Gfx::Engine;

namespace UI
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class Window: public IComponent
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Short constructor
		*/
		Window(const String& title);

		/*!
		** \brief Constructor
		*/
		Window(const String& title, size_t width, size_t height);

		//! Virtual destructor
		virtual ~Window();
		//@}

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
		//! Launch an event when the title has changed
		void fireInternalTitleChangedWL() { // TODO }

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

#endif // __YUNI_GFX_WINDOW_WINDOW_H__
