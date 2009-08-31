#ifdef __YUNI_GFX_TEXT_LABEL_H__
# define __YUNI_GFX_TEXT_LABEL_H__

# include "font.h"

namespace Yuni
{
namespace Gfx
{
	/*!
	** \brief A label is a graphic control for displaying text
	*/
	class Label
	{
	public:
		/*!
		** \brief Constructor
		**
		** \param font Font to use
		** \param text Text to display
		** \param left X coordinate to start drawing from
		** \param top Y coordinate to start drawing from
		** \param right Max X coordinate
		** \param bottom Max Y coordinate
		*/
		Label(const AFont::Ptr& font, const String& text, unsigned int left,
			  unsigned int top, unsigned int right = 0, unsigned int bottom = 0)
			: pFont(font), pLeft(left), pTop(top), pRight(right),
			  pBottom(bottom)
		{}

		//! Draw the label
		void draw() const
		{
			pFont->drawText(pText, pLeft, pTop, pRight, pBottom);
		}

		//! \name Visibility management
		//@{
		void visible(bool visibility) { pVisible = visibility; }
		bool visible() { return pVisible; }
		//@}

	private:
		AFont::Ptr pFont;
		String pText;
		bool pVisible;

		unsigned int pLeft;
		unsigned int pTop;
		unsigned int pRight;
		unsigned int pBottom;

	}; // Label

} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_TEXT_LABEL_H__
