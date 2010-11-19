
namespace Yuni
{
namespace Gfx
{
namespace Surface
{



	inline Cairo::Cairo()
		: pContext(NULL), pSurface(NULL)
	{
	}


	inline Cairo::~Cairo()
	{
		release();
	}


	inline void Cairo::resize(float, float)
	{
	}


	inline bool Cairo::refresh()
	{
		clearScreen();
		return true;
	}


	inline void Cairo::clearColor(const Color::RGB<float>& c)
	{
		cairo_set_source_rgb(pContext, c.red, c.green, c.blue);
	}


	inline void Cairo::clearColor(const Color::RGBA<float>& c)
	{
		cairo_set_source_rgba(pContext, c.red, c.green, c.blue, c.alpha);
	}


	inline void Cairo::clearScreen()
	{
		cairo_set_source_rgb(pContext, 0.3, 0.6, 0);
		cairo_fill(pContext);
		cairo_rectangle(pContext, 0.0, 0.0, 1.0, 1.0);
		cairo_paint(pContext);
	}



} // namespace Surface
} // namespace Gfx
} // namespace Yuni
