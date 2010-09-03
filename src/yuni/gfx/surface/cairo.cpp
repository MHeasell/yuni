
#include "cairo.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{


	bool Cairo::initialize()
	{
		return true;
	}

	void Cairo::release()
	{}

	void Cairo::resize(size_t, size_t)
	{
	}

	void Cairo::clearColor(Color::RGB<uint8>&)
	{}

	void Cairo::clearScreen()
	{}




} // namespace Surface
} // namespace Gfx
} // namespace Yuni
