#ifndef __YUNI_THREADS_MUTEX_HXX__
# define __YUNI_THREADS_MUTEX_HXX__


namespace Yuni
{


	inline Mutex::Mutex(const bool recursive)
	{
		if (recursive)
		{
			::pthread_mutexattr_t mutexattr;
			::pthread_mutexattr_init(&mutexattr);
			# if defined(YUNI_OS_DARWIN) || defined(YUNI_OS_FREEBSD) || defined(YUNI_OS_SOLARIS) || defined(YUNI_OS_SUNOS)
			::pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
			# else
			::pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);
			# endif
			::pthread_mutex_init(&pPthreadLock, &mutexattr);
			::pthread_mutexattr_destroy(&mutexattr);
		}
		else
		{
			::pthread_mutex_init(&pPthreadLock, NULL);
		}
	}


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



	inline MutexLocker::MutexLocker(Mutex& m)
		:pMutex(m)
	{
		m.lock();
	}


	inline MutexLocker::~MutexLocker()
	{
		pMutex.unlock();
	}


} // namespace Yuni


#endif // __YUNI_THREADS_MUTEX_HXX__
