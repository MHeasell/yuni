#ifndef __YUNI_GFX_WINDOW_WINDOW_H__
# define __YUNI_GFX_WINDOW_WINDOW_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/event/event.h"


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
	class AWindow : public IEventObserver<AWindow>, public Policy::ObjectLevelLockable<AWindow>
	{
	public:
		//! The threading policy
		typedef Policy::ObjectLevelLockable<AWindow> ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		AWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen);
		//! Destructor
		virtual ~AWindow();
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
		** \brief Resize the window
		**
		** This is implementation-dependent
		*/
		virtual void resize(unsigned int width, unsigned int height)
		{
			pWidth = width;
			pHeight = height;
		}


		/*!
		** \brief Get whether the window is in the process of closing
		*/
		bool closing() const;


		//! \name Title of the Window
		//@{
		//! Get the Title of the window
		const String& title() const { return pTitle; }
		//! Set the title of the window
		template<typename C> void title(const C& newTitle);
		//@}


		//! \name Vertical Synchronization (VSync)
		//@{
		//! Is vertical synchronization (VSync) currently active?
		virtual bool verticalSync() const;
		/*!
		** \brief Activate / deactivate vertical synchronization (VSync)
		**
		** \param active New value for vertical sync, true for active, false for inactive.
		** \return False if changing vertical sync failed. Yes, the stupid thing _can_ fail.
		*/
		virtual bool verticalSync(bool active);
		//@}


		//! \name Events
		//@{
		/*!
		** \brief Read the events in queue and launch the various handlers
		** \return True if events were processed, False otherwise
		*/
		virtual bool pollEvents() { return false; }

		virtual void onClose() { pClosing = true; }

		virtual void onMouseDown(float /* x */, float /* y */) {}
		virtual void onMouseClick(float /* x */, float /* y */) {}
		virtual void onMouseUp(float /* x */, float /* y */) {}
		virtual void onMouseWheel(float /* x */, float /* y */, float /* delta */) {}

		virtual void onKeyDown(unsigned char /* key */) {}
		virtual void onKeyPressed(unsigned char /* key */) {}
		virtual void onKeyUp(unsigned char /* key */) {}

		virtual void onFPSChanged(unsigned int /* FPS */) {}

		//@}

	protected:
		//! Swap the current buffer with the backbuffer
		virtual void onBlitWL() = 0;
		//! Method call when the title of the window has been changed
		virtual void onInternalTitleChangedWL() = 0;

	protected:
		String pTitle;
		unsigned int pWidth;
		unsigned int pHeight;
		unsigned int pBitDepth;
		bool pFullScreen;
		bool pClosing;

		// A friend !
		friend class Gfx::Engine;

	}; // class AWindow




} // namespace Window
} // namespace Gfx
} // namespace Yuni

# include "window.hxx"

#endif // __YUNI_GFX_WINDOW_WINDOW_H__
