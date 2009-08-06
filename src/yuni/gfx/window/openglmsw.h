#ifndef __YUNI_GFX_WINDOW_OPENGL_MSW_H__
# define __YUNI_GFX_WINDOW_OPENGL_MSW_H__

# include "../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../core/system/windows.hdr.h"
#	include "opengl.h"


namespace Yuni
{
namespace Gfx3D
{
namespace Window
{

	class OpenGLMSW: public OpenGL
	{
	public:
		OpenGLMSW(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:OpenGL(title, width, height, bitDepth, fullScreen)
		{}

		virtual bool initialize();
		virtual void close();
		virtual void blit() { SwapBuffers(pHDC); }

	private:
		HINSTANCE pHInstance;
		HWND pHWnd;
		HDC pHDC;
		HGLRC pHRC;

	}; // class OpenGLMSW




} // namespace Window
} // namespace Gfx3D
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_OPENGL_MSW_H__
