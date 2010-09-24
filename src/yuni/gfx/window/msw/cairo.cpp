
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline bool Cairo::initialize()
	{
		pSurface = cairo_win32_surface_create_with_ddb(GetDC(pHWND),
			cairo_format_t.CAIRO_FORMAT_ARGB32, (unsigned int)pWidth,
			(unsigned int)pHeight);
	}




} // namespace Window
} // namespace Gfx
} // namespace Yuni
