
#include "resolution.h"
#include "../../hash/checksum/md5.h"
#include "../../misc/math.h"


namespace Yuni
{
namespace System
{
namespace Devices
{
namespace Display
{

	const uint32 Resolution::MinWidth  = 640;   // 640x480
	const uint32 Resolution::MinHeight = 640;
	const uint32 Resolution::MaxWidth  = 2560;  // 2560x2048
	const uint32 Resolution::MaxHeight = 2048;



	Resolution::Resolution(const uint32 w, const uint32 h, const uint8 b)
	{
		pBitsPerPixel = (b == 32 ||  b == 24 || b == 16 || b == 8) ? b : 32;
		pWidth  = Math::MinMax<uint32>(w, MinWidth,  MaxWidth);
		pHeight = Math::MinMax<uint32>(h, MinHeight, MaxHeight);
	}


	Resolution::Resolution(const Resolution& c)
		:pWidth(c.pWidth), pHeight(c.pHeight), pBitsPerPixel(c.pBitsPerPixel)
	{}



	String Resolution::toString() const
	{
		String ret;
		ret << pWidth << "x" << pHeight;
		if (pBitsPerPixel)
			ret << " (" << (int)pBitsPerPixel << "Bits)";
		return ret;
	}



} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni


