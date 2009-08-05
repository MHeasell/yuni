#ifndef __YUNI_GFX3D_WINDOW_WINDOW__
# define __YUNI_GFX3D_WINDOW_WINDOW__

# include "../../yuni.h"
# include "../../core/string.h"



namespace Yuni
{
namespace Gfx3D
{
namespace Window
{


	/*!
	** \brief Abstraction of a window for graphic rendering
	*/
	class AWindow
	{
	public:
		AWindow(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:pTitle(title), pWidth(width), pHeight(height), pBitDepth(bitDepth), pFullScreen(fullScreen)
		{}
		virtual ~AWindow() {}

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

		//! \name Events
		//@{
		/*!
		** \brief Read the events in queue and launch the various handlers
		** \return True if events were processed, False otherwise
		*/
		virtual bool pollEvents() { return false; }

		virtual void onMouseDown(float /* x */, float /* y */) {}
		virtual void onMouseClick(float /* x */, float /* y */) {}
		virtual void onMouseUp(float /* x */, float /* y */) {}
		virtual void onMouseWheel(float /* x */, float /* y */, float /* delta */) {}

		virtual void onKeyDown(unsigned char /* key */) {}
		virtual void onKeyPressed(unsigned char /* key */) {}
		virtual void onKeyUp(unsigned char /* key */) {}
		//@}

	protected:
		String pTitle;
		unsigned int pWidth;
		unsigned int pHeight;
		unsigned int pBitDepth;
		bool pFullScreen;

	}; // class AWindow




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni

#endif // __YUNI_GFX3D_WINDOW_WINDOW__
