
#include "mutex.h"


namespace Yuni
{



	Mutex::Mutex(const bool recursive)
	{
		if (recursive)
		{
			pthread_mutexattr_t mutexattr;
			pthread_mutexattr_init(&mutexattr);
			# if defined(YUNI_OS_DARWIN) || defined(YUNI_OS_FREEBSD) || defined(YUNI_OS_SOLARIS) || defined(YUNI_OS_SUNOS)
			pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
			# else
			pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);
			# endif
			pthread_mutex_init(&pPthreadLock, &mutexattr);
			pthread_mutexattr_destroy(&mutexattr);
		}
		else
		{
			pthread_mutex_init(&pPthreadLock, NULL);
		}
	}



} // namespace Yuni

