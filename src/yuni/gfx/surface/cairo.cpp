
# include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{


	Cairo::Cairo()
	{
		pSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
		pContext = cairo_create(surface);
		clearColor(Color::RGB<uint8>(0, 0, 0));
	}


	Cairo::~Cairo()
	{}


	bool Cairo::initialize()
	{
		return true;
	}

	void Cairo::release()
	{}

	void Cairo::resize(float, float)
	{}

	bool Cairo::refresh()
	{
		cairo_paint(cr);
		return true;
	}

	void Cairo::clearColor(const Color::RGB<uint8>& c)
	{
		cairo_set_source_rgb(pContext, c.red / 255., c.green / 255., c.blue / 255.);
	}

	void Cairo::clearScreen()
	{}




} // namespace Surface
} // namespace Gfx
} // namespace Yuni
