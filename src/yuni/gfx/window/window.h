
#ifndef __YUNI_GFX3D_WINDOW_AWINDOW__
# define __YUNI_GFX3D_WINDOW_AWINDOW__

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

		virtual void onMouseDown(unsigned int x, unsigned int y) {}
		virtual void onMouseClick(unsigned int x, unsigned int y) {}
		virtual void onMouseUp(unsigned int x, unsigned int y) {}
		virtual void onMouseWheel(unsigned int x, unsigned int y, float delta) {}

		virtual void onKeyDown(unsigned int key) {}
		virtual void onKeyPressed(unsigned int key) {}
		virtual void onKeyUp(unsigned int key) {}

		//@}

	protected:
		String pTitle;
		unsigned int pWidth;
		unsigned int pHeight;
		unsigned int pBitDepth;
		bool pFullScreen;

	}; // AWindow

} // Window
} // Gfx3D
} // Yuni

#endif // __YUNI_GFX3D_WINDOW_AWINDOW__
