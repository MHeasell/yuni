
#include "sound3D.h"


namespace Yuni
{
namespace Audio
{


	bool Sound3D::prepare()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return loadFromFileWL();
	}


	unsigned int Sound3D::buffer() const
	{
		return pBufferID;
	}




} // namespace Audio
} // namespace Yuni
