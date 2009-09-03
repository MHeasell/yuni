#ifndef __YUNI_GFX_TEXT_WGL_H__
# define __YUNI_GFX_TEXT_WGL_H__

# include "../../yuni.h"

# ifdef YUNI_WINDOWSYSTEM_MSW
#	include "../../core/system/windows.hdr.h"
#	include "../api/gl.h"
#	include "./font.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief MSWindows with OpenGL-specific implementation of a font
	*/
	class WGLFont: public AFont
	{
	public:
		WGLFont(const String& fontFace, unsigned int size, bool bold = false, bool italic = false);
		~WGLFont();

		virtual void drawText(const String& text, unsigned int left, unsigned int top,
			unsigned int right, unsigned int bottom);

	private:
		bool createFont();

	private:
		HFONT pFont;
		bool pInitialized;
		GLuint pDisplayList;

	}; // WGLFont

} // namespace Gfx
} // namespace Yuni

#endif // YUNI_WINDOWSYSTEM_MSW

#endif // __YUNI_GFX_TEXT_WGL_H__

