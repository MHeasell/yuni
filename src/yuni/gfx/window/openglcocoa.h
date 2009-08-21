#ifndef __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
# define __YUNI_GFX_WINDOW_OPENGL_COCOA_H__

# include "../../yuni.h"
# include "window.h"
# include "../render/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	class OpenGLCocoa: public AWindow, public Render::OpenGL
	{
	public:
		OpenGLCocoa(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AWindow(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize() { return AOpenGL::initialize(); }
		virtual void close() { AOpenGL::release(); }
		// virtual bool pollEvents();


	protected:
		void onBlitWL() {}
		void onInternalTitleChangedWL() {}

	}; // class OpenGLCocoa




} // namespace Window
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
