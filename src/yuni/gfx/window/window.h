#ifndef __YUNI_GFX_WINDOW_WINDOW_H__
# define __YUNI_GFX_WINDOW_WINDOW_H__

# include <map>
# include "../../yuni.h"
# include "../device.h"
# include "../../core/string.h"
# include "../../core/event/event.h"
# include "../../thread/policy.h"
# include "../surface/surface.h"
# include "../../ui/component.h"
# include "../../ui/desktop.h"

namespace Yuni
{
namespace Gfx
{

	// Forward declaration
	class Engine;


namespace Window
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class IWindow: public Policy::ObjectLevelLockable<IWindow>
	{
	public:
		//! Threading policy
		typedef Policy::ObjectLevelLockable<IWindow> ThreadingPolicy;
		//! Window map
		typedef std::map<sint64, IWindow> Map;
		//! Smart pointer
		typedef SmartPtr<IWindow> Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		IWindow(UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen);
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

		/*!
		** \brief Resize the component
		*/
		virtual void resize(float width, float height);

		//! Get the UI window that corresponds to this internal representation
		virtual UI::Window::Ptr window() { return pWindow; }


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

	protected:
		virtual void onFPSChanged(unsigned int /* FPS */) {}

		//@}

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh() = 0;

		//! Swap the current buffer with the backbuffer
		virtual void blitWL() = 0;

		//! Method call when the title of the window has been changed
		virtual void onInternalTitleChangedWL() = 0;

	protected:
		//! Corresponding UI window
		UI::Window::Ptr pWindow;

		unsigned int pBitDepth;
		bool pFullScreen;
		bool pClosing;

		// A friend !
		friend class Gfx::Engine;

	}; // class IWindow



	/*!
	** \brief Create a platform-dependent window.
	**
	** The characteristics of this window and its associated rendering surface
	** will be determined using the device.
	*/
	IWindow* Create(UI::Window::Ptr& source, const Device::Ptr& device);




} // namespace Window
} // namespace Gfx
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_GFX_WINDOW_WINDOW_H__
