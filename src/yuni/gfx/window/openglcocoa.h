#ifndef __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
# define __YUNI_GFX_WINDOW_OPENGL_COCOA_H__

# include "../../yuni.h"
# include "window.h"
# include "opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	class OpenGLCocoa: public Window, public AOpenGL
	{
	public:
		OpenGLCocoa(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:OpenGL(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize() { return AOpenGL::initialize(); }
		virtual void close() { AOpenGL::release(); }
		virtual void blit() {}
		// virtual bool pollEvents();

		virtual void onTitleChanged() {}

	}; // class OpenGLCocoa




} // namespace Window
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
