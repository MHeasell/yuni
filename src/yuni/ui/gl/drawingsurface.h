#ifndef __YUNI_UI_DRAWINGSURFACE_H__
# define __YUNI_UI_DRAWINGSURFACE_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/color/rgba.h"
# include "../../core/point2D.h"
# include <cassert>
# include "../font.h"
# include "texture.h"

namespace Yuni
{
namespace UI
{

	//! Forward declaration
	class DrawingSurfaceImpl;


	/*!
	** \brief A rectangle surface for 2D drawing
	*/
	class DrawingSurface
	{
	public:
		//! Smart pointer
		typedef SmartPtr<DrawingSurface>  Ptr;


	public:
		//! Constructor to an empty transparent surface
		DrawingSurface(uint width, uint height);

		//! Destructor
		~DrawingSurface();

		//! Begin modifications on the surface
		void begin();

		//! Apply modifications on the surface
		void commit();

		//! Discard modifications on the surface
		void rollback();

		//! Clear the surface
		void clear();

		//! Resize the surface
		void resize(uint width, uint height);

		//! Draw text on the surface
		void drawText(const String& text, const Font::Ptr& font, const Color::RGBA<float>& color,
			int x, int y);

		//! Draw text on the surface, centered and clipped in a rectangle
		void drawTextInRect(const String& text, const Font::Ptr& font,
			const Color::RGBA<float>& color, int x, int y, uint width, uint height);

		//! Draw text on the surface
		void drawLine(const Color::RGBA<float>& color, int startX, int startY, int endX, int endY,
			float lineWidth);

		//! Draw a rectangle on the surface
		void drawRectangle(const Color::RGBA<float>& frontColor, const Color::RGBA<float>& backColor,
			int x, int y, uint width, uint height, float lineWidth);

		//! Activate clipping inside a rectangle
		void beginRectangleClipping(int x, int y, uint width, uint height);

		//! Disable last clipping, must be called in pair with begin*Clipping
		void endClipping();

		//! Get the texture containing the rendering of this surface
		const Gfx3D::Texture::Ptr& texture() const;

		//! Get the current width of the surface
		uint width() const;

		//! Get the current height of the surface
		uint height() const;

	private:
		//! Update the texture according to the changes in the surface
		void updateTexture();

	private:
		DrawingSurfaceImpl* pImpl;

	}; // class DrawingSurface


} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_DRAWINGSURFACE_H__
