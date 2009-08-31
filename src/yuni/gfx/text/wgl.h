#ifndef __YUNI_GFX_TEXT_WGL_H__
# define __YUNI_GFX_TEXT_WGL_H__

# include "font.h"

namespace Yuni
{
namespace Gfx
{
namespace Text
{

	/*!
	** \brief MSWindows with OpenGL-specific implementation of a font
	*/
	class WGLFont: public AFont
	{
	public:
		WGLFont(const String& fontFace, unsigned int size, bool bold = false,
			bool italic = false)
			: AFont(fontFace, size, bold, italic)
		{}
		~WGLFont() {}

		virtual void drawText(const String& text, unsigned int left, unsigned int top,
			unsigned int right, unsigned int bottom) const;

	}; // WGLFont

} // namespace Text
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_TEXT_WGL_H__

