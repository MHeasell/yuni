
#include <windows.h>
#include "opengl.h"

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

	}; // OpenGLMSW

} // Window
} // Gfx3D
} // Yuni

#include "openglmsw.hxx"
