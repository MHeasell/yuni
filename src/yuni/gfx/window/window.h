#ifndef __YUNI_GFX_WINDOW_WINDOW__
# define __YUNI_GFX_WINDOW_WINDOW__

# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/event/event.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class AWindow: public Event::Observer<AWindow>
	{
	public:
		AWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:pTitle(title), pWidth(width), pHeight(height), pBitDepth(bitDepth), pFullScreen(fullScreen), pClosing(false)
		{}
		virtual ~AWindow() { destroyingObserver(); }

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
		** \brief Swap the current buffer with the backbuffer
		**
		** This is implementation-dependent
		*/
		virtual void blit() = 0;

		/*!
		** \brief Get whether the window is in the process of closing
		*/
		bool closing() { return pClosing; }


		//! \name Accessors
		//@{

		//! Title of the window
		const String& title() const { return pTitle; }
		void title(const String& newTitle)
		{
			pTitle = newTitle;
			onTitleChanged();
		}

		//! Is vertical synchronization (VSync) currently active?
		virtual bool verticalSync() const { return true; }
		/*!
		** \brief Activate / deactivate vertical synchronization (VSync)
		**
		** \param active New value for vertical sync, true for active, false for inactive.
		** \return False if changing vertical sync failed. Yes, the stupid thing _can_ fail.
		*/
		virtual bool verticalSync(bool /* active */) { return false; }

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
		virtual void onTitleChanged() {}

		//@}

	protected:
		String pTitle;
		unsigned int pWidth;
		unsigned int pHeight;
		unsigned int pBitDepth;
		bool pFullScreen;
		bool pClosing;

	}; // class AWindow




} // namespace Window
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_WINDOW_WINDOW__
