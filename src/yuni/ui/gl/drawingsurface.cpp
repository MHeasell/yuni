# include "drawingsurface.h"
# include "../../io/file.h"
# include "../../private/graphics/opengl/glew/glew.h"
# include "framebuffer.h"
# include <stack>
# include "vase_rend_draft_2.h"

namespace Yuni
{
namespace UI
{


	/*!
	** \brief Implementation details for a DrawingSurface
	*/
	class DrawingSurfaceImpl
	{
	public:
		//! Clipping coordinates
		typedef std::pair<Point2D<int>, Point2D<int> > ClipCoord;

		//! Stack type to store clipping coordinates
		typedef std::stack<ClipCoord>  ClipStack;

	public:
		DrawingSurfaceImpl(uint width, uint height);
		~DrawingSurfaceImpl();

	public:
		//! Surface size
		Point2D<uint> size;

		//! Is the surface locked for drawing ?
		bool locked;

		//! Stack containing the current clipping regions
		ClipStack clippings;

		//! Frame buffer to render to
		Gfx3D::FrameBuffer fb;

		GLint previousFB;

	}; // class DrawingSurfaceImpl



	DrawingSurfaceImpl::DrawingSurfaceImpl(uint width, uint height):
		size(width, height),
		locked(false),
		fb(width, height)
	{
		fb.initialize(Gfx3D::FrameBuffer::fbDraw);
	}


	DrawingSurfaceImpl::~DrawingSurfaceImpl()
	{
	}



	///////////////////// DrawingSurface


	DrawingSurface::DrawingSurface(uint width, uint height):
		pImpl(new DrawingSurfaceImpl(width, height))
	{
	}


	DrawingSurface::~DrawingSurface()
	{
		delete pImpl;
	}


	void DrawingSurface::begin()
	{
		assert(!pImpl->locked && "DrawingSurface error : Cannot begin drawing on a locked surface !");
		pImpl->locked = true;

		::glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &pImpl->previousFB);
		pImpl->fb.activate();
		::glPushAttrib(GL_ENABLE_BIT);
		//::glEnable(GL_SCISSOR_TEST);
		beginRectangleClipping(0, 0, pImpl->size.x, pImpl->size.y);
		clear();
	}


	void DrawingSurface::commit()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot commit on an unlocked surface ! (try calling the begin() function)");
		endClipping();
		pImpl->locked = false;
		assert(pImpl->clippings.empty() && "DrawingSurface commit : Too few endClipping() calls, stack is not empty !");
		::glPopAttrib();
		pImpl->fb.deactivate();
		::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 1/*pImpl->previousFB*/);
	}


	void DrawingSurface::rollback()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot rollback on an unlocked surface ! (try calling the begin() function)");
		pImpl->locked = false;
		::glPopAttrib();
		pImpl->fb.deactivate();
	}


	void DrawingSurface::clear()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot clear an unlocked surface !");
		::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void DrawingSurface::resize(uint width, uint height)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot resize an unlocked surface !");
		auto& size = pImpl->size;
		if (width == size.x && height == size.y)
			return;
		size(width, height);
		pImpl->fb.resize(width, height);
	}


	void DrawingSurface::drawText(const String& text, const Font::Ptr& font,
		const Color::RGBA<float>& color, int x, int y)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");
		// TODO
	}


	void DrawingSurface::drawTextInRect(const String& text, const Font::Ptr& font,
		const Color::RGBA<float>& color, int x, int y, uint width, uint height)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");
		beginRectangleClipping(x, y, width, height);
		drawText(text, font, color, x, y);
		endClipping();
	}


	void DrawingSurface::drawLine(const Color::RGBA<float>& color, int startX, int startY,
		int endX, int endY, uint lineWidth)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");
		line((double)startX, (double)startY, (double)endX, (double)endY, (float)lineWidth,
			color.red, color.green, color.blue, color.alpha, 0, 0, true);
	}


	void DrawingSurface::drawRectangle(const Color::RGBA<float>& frontColor,
		const Color::RGBA<float>& backColor, int x, int y, uint width, uint height, uint lineWidth)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");

		// Draw the back as a quad with the proper color
		::glBegin(GL_QUADS);
		::glColor4f(backColor.red, backColor.green, backColor.blue, backColor.alpha);
		::glVertex2f(x, y);
		::glVertex2f(x + width, y);
		::glVertex2f(x + width, y + height);
		::glVertex2f(x, y + height);
		::glEnd();

		::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


		// Top line
		line((double)x, (double)y, (double)(x + width), (double)y, (float)lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Bottom line
		line((double)x, (double)(y + height), (double)(x + width), (double)(y + height), (float)lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Left line
		line((double)x, (double)y, (double)x, (double)(y + height), (float)lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Right line
		line((double)(x + width), (double)y, (double)(x + width), (double)(y + height), (float)lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
	}


	void DrawingSurface::beginRectangleClipping(int x, int y, uint width, uint height)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot manage clipping on an unlocked surface !");
		::glScissor(x, y, width, height);
		pImpl->clippings.push(DrawingSurfaceImpl::ClipCoord(Point2D<int>(x, y), Point2D<int>(width, height)));
	}


	void DrawingSurface::endClipping()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot manage clipping on an unlocked surface !");
		pImpl->clippings.pop();
		if (!pImpl->clippings.empty())
		{
			// Reapply previous clipping
			const auto& coord = pImpl->clippings.top();
			::glScissor(coord.first.x, coord.first.y, coord.second.x, coord.second.y);
		}
	}


	const Gfx3D::Texture::Ptr& DrawingSurface::texture() const
	{
		return pImpl->fb.texture();
	}


	uint DrawingSurface::width() const
	{
		return pImpl->size.x;
	}


	uint DrawingSurface::height() const
	{
		return pImpl->size.y;
	}



} // namespace Cairo
} // namespace Yuni
