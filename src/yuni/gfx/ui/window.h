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
	class IWindow: IComponent
	{

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		IWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen);
		//! Destructor
		virtual ~IWindow();
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
		virtual void close() = 0;

		/*!
		** \brief Get whether the window is in the process of closing
		*/
		bool closing() const;


		//! Get the UI desktop, basis for all UI in this window
		virtual Desktop desktop() { return pUI; }


		//! \name Title of the Window
		//@{
		//! Get the Title of the window
		const String& title() const { return pTitle; }
		//! Set the title of the window
		template<typename C> void title(const C& newTitle);
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
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh() = 0;

		//! Method call when the title of the window has been changed
		virtual void onInternalTitleChangedWL() = 0;

	protected:

		/*!
		** \brief Title of the window
		*/
		String pTitle;
		unsigned int pBitDepth;
		bool pFullScreen;
		bool pClosing;


	}; // class IWindow



	/*!
	** \brief Create a platform-dependent window.
	**
	** The characteristics of this window and its associated rendering surface
	** will be determined using the device.
	*/
	IWindow* Create(const String& title, const Device::Ptr& device);



} // namespace UI
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_GFX_WINDOW_WINDOW_H__
