#ifndef __YUNI_GFX_WINDOW_OPENGL_MSW_H__
# define __YUNI_GFX_WINDOW_OPENGL_MSW_H__

# include "../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../core/system/windows.hdr.h"
#	include "msw.h"
#	include "opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	class OpenGLMSW: public AMSWindows, public AOpenGL
	{
	public:
		//! The Threading Policy
		typedef AMSWindows::ThreadingPolicy ThreadingPolicy;

	public:
		OpenGLMSW(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:AMSWindows(title, width, height, bitDepth, fullScreen)
		{
			pWindowClassName = "OpenGL";
		}

		virtual bool initialize();
		virtual void close();
		virtual void resize(unsigned int width, unsigned int height);

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

	protected:
		void onBlitWL();

	private:
		HDC pHDC;
		HGLRC pHRC;

	}; // class OpenGLMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_OPENGL_MSW_H__
