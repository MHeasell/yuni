#ifndef __YUNI_THREADS_MUTEX_HXX__
# define __YUNI_THREADS_MUTEX_HXX__


namespace Yuni
{


	inline Mutex::~Mutex()
	{
		pthread_mutex_destroy(&pPthreadLock);
	}


	inline void Mutex::lock()
	{
		pthread_mutex_lock(&pPthreadLock);
	}


	inline void Mutex::unlock()
	{
		pthread_mutex_unlock(&pPthreadLock);
	}


	inline pthread_mutex_t& Mutex::pthreadMutex()
	{
		return pPthreadLock;
	}





} // namespace Yuni


#endif // __YUNI_THREADS_MUTEX_HXX__
