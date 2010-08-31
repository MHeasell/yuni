#ifndef __YUNI_GFX_WINDOW_OPENGL_MSW_H__
# define __YUNI_GFX_WINDOW_OPENGL_MSW_H__

# include "../../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../../core/system/windows.hdr.h"
#	include "msw.h"
#	include "../../surface/opengl.h"


namespace Yuni
{
namespace Gfx
{
namespace Window
{

	/*!
	** \brief Microsoft Windows-specific window, using an OpenGL surface
	*/
	class OpenGLMSW: public IMSWindows, public Surface::OpenGL
	{
	public:
		//! The Threading Policy
		typedef IMSWindows::ThreadingPolicy ThreadingPolicy;

	public:
		OpenGLMSW(const String& title, unsigned int width, unsigned int height, unsigned int bitDepth, bool fullScreen)
			:IMSWindows(title, width, height, bitDepth, fullScreen)
		{
			pWindowClassName = "OpenGL";
		}

		virtual bool initialize();
		virtual void close();
		virtual void resize(unsigned int width, unsigned int height);
		virtual Surface::OpenGL* surface() { return this; }

		//! Is vertical synchronization (VSync) active?
		virtual bool verticalSync() const;
		//! Activate / deactivate vertical synchronization (VSync)
		virtual bool verticalSync(bool activate);

	protected:
		/*!
		** \brief Refresh the window content if necessary
		**
		** \returns Always refresh in OpenGL view
		*/
		virtual bool refresh() { return true; }
		virtual void blitWL();

	private:
		HDC pHDC;
		HGLRC pHRC;

	}; // class OpenGLMSW




} // namespace Window
} // namespace Gfx
} // namespace Yuni


# endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_WINDOW_OPENGL_MSW_H__
