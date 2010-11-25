
namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
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
		pContext = cairo_create(pSurface);
		assert(cairo_status(pContext) == CAIRO_STATUS_SUCCESS && "Cairo context creation failed !");
	}


	inline bool Cairo::refresh()
	{
		pContext = cairo_create(pSurface);
		assert(cairo_status(pContext) == CAIRO_STATUS_SUCCESS && "Cairo context creation failed !");
		clearScreen();
		return true;
	}


	inline void Cairo::clearColor(const Yuni::Color::RGB<float>& c)
	{
		cairo_set_source_rgb(pContext, c.red, c.green, c.blue);
	}


	inline void Cairo::clearColor(const Yuni::Color::RGBA<float>& c)
	{
		cairo_set_source_rgba(pContext, c.red, c.green, c.blue, c.alpha);
	}


	inline void Cairo::clearScreen()
	{
		cairo_set_source_rgb(pContext, 1.0, 0.0, 0.0);
		cairo_rectangle(pContext, 0, 0, 255, 255);
		cairo_fill(pContext);
	}



} // namespace Surface
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
