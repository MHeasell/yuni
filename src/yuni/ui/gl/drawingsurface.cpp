# include "drawingsurface.h"
# include "../../io/file.h"
# include "../../private/graphics/opengl/glew/glew.h"
# include "framebuffer.h"
# include "shadermanager.h"
# include "linerenderer.h"
# include <vector>

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
		typedef std::vector<ClipCoord>  ClipStack;

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

		//! Store previous frame-buffer value to restore it after drawing
		GLint previousFB;

		//! Shader program used to draw lines in the drawing surface
		Gfx3D::ShaderProgram::Ptr lineShader;

		//! Shader program used to draw everything else in the drawing surface
		Gfx3D::ShaderProgram::Ptr baseShader;

	}; // class DrawingSurfaceImpl



	DrawingSurfaceImpl::DrawingSurfaceImpl(uint width, uint height):
		size(width, height),
		locked(false),
		fb(width, height)
	{
		fb.initialize(Gfx3D::FrameBuffer::fbDraw);
		baseShader = Gfx3D::ShaderManager::Instance().get("data/shaders/transformonly.vert", "data/shaders/uniformcolor.frag");
		if (!baseShader)
		{
			std::cerr << "Shader loading or compilation for UI drawing failed ! " << std::endl;
			baseShader = nullptr;
		}
		else
		{
			baseShader->bindAttribute("attrVertex", Yuni::Gfx3D::Vertex<>::vaPosition);
			if (!baseShader->load())
			{
				std::cerr << "Shader program link for UI drawing failed !" << std::endl
						  << baseShader->errorMessage() << std::endl;
				baseShader = nullptr;
			}
		}

		lineShader = Gfx3D::ShaderManager::Instance().get("data/shaders/colorattr.vert", "data/shaders/colorattr.frag");
		if (!lineShader)
		{
			std::cerr << "Shader loading or compilation for line drawing failed !" << std::endl;
			lineShader = nullptr;
			return;
		}
		else
		{
			lineShader->bindAttribute("attrVertex", Gfx3D::Vertex<>::vaPosition);
			lineShader->bindAttribute("attrColor", Gfx3D::Vertex<>::vaColor);
			if (!lineShader->load())
			{
				std::cerr << "Shader program link for line drawing failed !" << std::endl
						  << lineShader->errorMessage() << std::endl;
				lineShader = nullptr;
			}
		}
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
		assert(pImpl->baseShader->valid() && "Shaders were not properly loaded, cannot continue !");
		assert(pImpl->lineShader->valid() && "Shaders were not properly loaded, cannot continue !");

		pImpl->locked = true;

		// Set view matrices for 2D overlay display
		::glMatrixMode(GL_PROJECTION);
		::glPushMatrix();
		::glLoadIdentity();
		// Window coordinates : [0,0] at top-left, [width,height] at bottom-right
		::gluOrtho2D(0.0f, pImpl->size.x, pImpl->size.y, 0.0f);

		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glLoadIdentity();

		// Store the previous framebuffer value
		::glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &pImpl->previousFB);
		// Bind framebuffer
		pImpl->fb.activate();
		// Bind shaders
		pImpl->baseShader->activate();

		// Clip on drawing surface
		::glPushAttrib(GL_ENABLE_BIT);
		::glEnable(GL_SCISSOR_TEST);
		::glEnable(GL_BLEND);
		clear();
	}


	void DrawingSurface::commit()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot commit on an unlocked surface ! (try calling the begin() function)");
		//endClipping();
		assert(pImpl->clippings.empty() && "DrawingSurface commit : Too few endClipping() calls, stack is not empty !");
		pImpl->locked = false;

		::glMatrixMode(GL_PROJECTION);
		::glPopMatrix();
		::glMatrixMode(GL_MODELVIEW);
		::glPopMatrix();
		::glPopAttrib();
		pImpl->baseShader->deactivate();
		pImpl->fb.deactivate();
		::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 1/*pImpl->previousFB*/);
	}


	void DrawingSurface::rollback()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot rollback on an unlocked surface ! (try calling the begin() function)");
		pImpl->clippings.clear();
		pImpl->locked = false;

		::glMatrixMode(GL_PROJECTION);
		::glPopMatrix();
		::glMatrixMode(GL_MODELVIEW);
		::glPopMatrix();
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
		int endX, int endY, float lineWidth)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");
		::glEnableClientState(GL_VERTEX_ARRAY);
		::glEnableClientState(GL_COLOR_ARRAY);
		line((double)startX, (double)startY, (double)endX, (double)endY, lineWidth,
			 color.red, color.green, color.blue, color.alpha, 0, 0, true);
		::glDisableClientState(GL_VERTEX_ARRAY);
		::glDisableClientState(GL_COLOR_ARRAY);
	}


	void DrawingSurface::drawRectangle(const Color::RGBA<float>& frontColor,
		const Color::RGBA<float>& backColor, int x, int y, uint width, uint height, float lineWidth)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot draw to an unlocked surface !");

		// Draw the back as a quad with the proper color
		pImpl->baseShader->bindUniform("Color", backColor);
		const float vertices[] =
			{
				(float)x, (float)(y + height),
				(float)x, (float)y,
				(float)(x + width), (float)y,
				(float)x, (float)(y + height),
				(float)(x + width), (float)y,
				(float)(x + width), (float)(y + height)
			};
		::glEnableVertexAttribArray(Gfx3D::Vertex<>::vaPosition);
		::glVertexAttribPointer(Gfx3D::Vertex<>::vaPosition, 2, GL_FLOAT, false, 0, vertices);
		// Draw
		::glDrawArrays(GL_TRIANGLES, 0, 6);
		::glDisableVertexAttribArray(Gfx3D::Vertex<>::vaPosition);

		pImpl->lineShader->activate();

		// Top line
		line((double)x, (double)y, (double)(x + width), (double)y, lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Bottom line
		line((double)x, (double)(y + height) - lineWidth,
			(double)(x + width), (double)(y + height) - lineWidth, lineWidth,
			 frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Left line
		line((double)x, (double)y, (double)x, (double)(y + height), lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);
		// Right line
		line((double)(x + width) - lineWidth, (double)y,
			(double)(x + width) - lineWidth, (double)(y + height), lineWidth,
			frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha, .0f, .0f, true);

		pImpl->baseShader->activate();
	}


	void DrawingSurface::beginRectangleClipping(int x, int y, uint width, uint height)
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot manage clipping on an unlocked surface !");
		::glScissor(x, y, width, height);
		pImpl->clippings.push_back(DrawingSurfaceImpl::ClipCoord(Point2D<int>(x, y), Point2D<int>(width, height)));
	}


	void DrawingSurface::endClipping()
	{
		assert(pImpl->locked && "DrawingSurface error : Cannot manage clipping on an unlocked surface !");
		pImpl->clippings.pop_back();
		if (!pImpl->clippings.empty())
		{
			// Reapply previous clipping
			const auto& coord = pImpl->clippings.back();
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
