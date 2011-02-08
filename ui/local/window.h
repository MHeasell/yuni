#ifndef __YUNI_PRIVATE_UI_LOCAL_WINDOW_H__
# define __YUNI_PRIVATE_UI_LOCAL_WINDOW_H__

# include <map>
# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/event.h"
# include "../../thread/policy.h"
# include "../window.h"
# include "../../gfx/device.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class IWindow: public IEventObserver<IWindow>
	{
	public:
		//! Threading policy
		typedef IEventObserver<IWindow>::ThreadingPolicy ThreadingPolicy;
		//! Smart pointer
		typedef SmartPtr<IWindow> Ptr;


	public:
		/*!
		** \brief Create a platform-dependent window.
		**
		** The characteristics of this window and its associated rendering surface
		** will be determined using the device.
		*/
		static IWindow* Create(const Yuni::UI::Window::Ptr& source);


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		IWindow(const Yuni::UI::Window::Ptr& source, unsigned int bitDepth, bool fullScreen);
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
		** \brief Resize the local window
		*/
		virtual void resize(float width, float height) = 0;

		//! Get the UI window that corresponds to this internal representation
		virtual Yuni::UI::Window::Ptr window() const { return pUIWnd; }

		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns True if the window was refreshed, false if it was not necessary
		*/
		virtual bool refresh() = 0;

		//! \name Events
		//@{
		/*!
		** \brief Read the events in queue and launch the various handlers
		** \return True if events were processed, False otherwise
		*/
		virtual bool pollEvents() { return false; }


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
		//! Corresponding UI window
		Yuni::UI::Window::Ptr pUIWnd;

		unsigned int pBitDepth;
		bool pFullScreen;

	}; // class IWindow



} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_PRIVATE_UI_LOCAL_WINDOW_H__
