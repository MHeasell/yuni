#ifndef __YUNI_GFX_TEXT_FONT_H__
# define __YUNI_GFX_TEXT_FONT_H__

# include "../../core/string.h"
# include "../../core/smartptr.h"

namespace Yuni
{
namespace Gfx
{

	/*!
	** \brief Generic font representation
	*/
	class AFont
	{
	public:
		typedef SmartPtr<AFont> Ptr;

	public:
		AFont(const String& fontFace, unsigned int size, bool bold = false,
			bool italic = false)
			: pFace(fontFace), pSize(size), pBold(bold), pItalic(italic)
		{}
		virtual ~AFont() {}

		virtual void drawText(const String& text, unsigned int left, unsigned int top,
			unsigned int right, unsigned int bottom) = 0;

	protected:
		String pFace;
		unsigned int pSize;
		bool pBold;
		bool pItalic;

	}; // AFont

} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_TEXT_FONT_H__
