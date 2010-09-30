
# include "cairo.h"

namespace Yuni
{
namespace Gfx
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



} // namespace Surface
} // namespace Gfx
} // namespace Yuni
