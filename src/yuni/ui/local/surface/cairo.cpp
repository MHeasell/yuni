
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
		// Default color is red
		pClearColor.assign(1.0f, 0.0f, 0.0f);
		return false;
	}


	bool Cairo::refresh()
	{
		pContext = cairo_create(pSurface);
		if (cairo_status(pContext) != CAIRO_STATUS_SUCCESS)
		{
			std::cout << cairo_status_to_string(cairo_status(pContext)) << std::endl;
			assert(false && "Cairo context creation failed !");
		}
		clearScreen();
		release();
		return true;
	}



} // namespace Surface
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
