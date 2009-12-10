#include "sound3D.h"

namespace Yuni
{
namespace Audio
{

	bool Sound3D::prepare()
	{
		if (!loadFile())
			return false;
		return true;
	}

	unsigned int Sound3D::buffer()
	{
		return pBufferID;
	}

} // namespace Audio
} // namespace Yuni
