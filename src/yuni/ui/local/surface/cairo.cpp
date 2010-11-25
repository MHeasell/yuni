
# include "cairo.h"

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


	void Cairo::release()
	{
		if (pContext)
			cairo_destroy(pContext);
		if (pSurface)
			cairo_surface_destroy(pSurface);
		pContext = NULL;
		pSurface = NULL;
	}


	bool Cairo::initialize()
	{
		pContext = cairo_create(pSurface);
		assert(cairo_status(pContext) == CAIRO_STATUS_SUCCESS && "Cairo context creation failed !");
		cairo_set_source_rgb(pContext, 1, 0, 0);
		return false;
	}



} // namespace Surface
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
