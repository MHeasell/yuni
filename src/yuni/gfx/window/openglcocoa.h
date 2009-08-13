#ifndef __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
# define __YUNI_GFX_WINDOW_OPENGL_COCOA_H__

# include "../../yuni.h"
# include "opengl.h"


namespace Yuni
{
namespace Gfx3D
{
namespace Window
{

	class OpenGLCocoa: public OpenGL
	{
	public:
		OpenGLCocoa(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:OpenGL(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize() { return OpenGL::initialize(); }
		virtual void close() { OpenGL::close(); }
		virtual void blit() {}
		// virtual bool pollEvents();

		virtual void onTitleChanged() {}

	}; // class OpenGLCocoa




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni


#endif // __YUNI_GFX_WINDOW_OPENGL_COCOA_H__
