#ifndef __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
# define __YUNI_GFX_WINDOW_OPENGL_COCOA_H__

# include "../../../yuni.h"
# include "../window.h"
# include "../../surface/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Mac OS X, Cocoa-specific window, using an OpenGL surface
	*/
	class OpenGLCocoa: public AWindow, public Surface::OpenGL
	{
	public:
		OpenGLCocoa(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AWindow(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize() { return Surface::OpenGL::initialize(); }
		virtual void close() { Surface::OpenGL::release(); }
		virtual Surface::OpenGL* surface() { return this; }

		// virtual bool pollEvents();


	protected:
		void onBlitWL() {}
		void onInternalTitleChangedWL() {}

	}; // class OpenGLCocoa




} // namespace Window
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
