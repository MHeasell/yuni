
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


	inline bool Cairo::initialize()
	{
		pContext = cairo_create(pSurface);
		clearColor(Color::RGB<float>(0, 0, 0));
		return true;
	}


	inline void Cairo::resize(float, float)
	{
	}


	inline bool Cairo::refresh()
	{
		cairo_paint(pContext);
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
		cairo_fill(pContext);
	}



} // namespace Surface
} // namespace Gfx
} // namespace Yuni
