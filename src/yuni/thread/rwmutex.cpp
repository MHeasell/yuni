
#include "rwmutex.h"


namespace Yuni
{


	void RWMutex::writeLock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pMutex.lock();
		pSemaphore.acquire(pMaxReaders);
		pMutex.unlock();
		# endif
	}


	void RWMutex::writeUnlock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pMutex.lock();
		pSemaphore.release(pMaxReaders);
		pMutex.unlock();
		# endif
	}




} // namespace Yuni


