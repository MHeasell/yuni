
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{


	bool Cairo::initialize()
	{}

	void Cairo::release()
	{}

	void Cairo::resize(unsigned int width, unsigned int height)
	{}

	template<typename ColorT>
	virtual void Cairo::clearColor(ColorT& newColor)
	{}

	virtual void Cairo::clearScreen()
	{}


	}; // Cairo



} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_CAIRO_H__
