
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline bool Cairo::initialize()
	{
		 = cairo_win32_surface_create_with_ddb(GetDC(pHWND),
			cairo_format_t.CAIRO_FORMAT_ARGB32, pWidth, pHeight);
	}




} // namespace Window
} // namespace Gfx
} // namespace Yuni
