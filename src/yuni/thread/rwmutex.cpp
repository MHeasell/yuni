
#include "rwmutex.h"


namespace Yuni
{


	inline void RWMutex::writeLock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pMutex.lock();
		pSemaphore.acquire(pMaxReaders);
		pMutex.unlock();
		# endif
	}


	inline void RWMutex::writeUnlock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pMutex.lock();
		pSemaphore.release(pMaxReaders);
		pMutex.unlock();
		# endif
	}




} // namespace Yuni


