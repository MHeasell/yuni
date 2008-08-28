
#include <yuni/yuni.h>
#include <yuni/threads/mutex.h>


namespace Yuni
{


	Mutex::Mutex()
	{
		//pthread_mutexattr_t mutexattr;
		/*
		pthread_mutexattr_init(&mutexattr);
		# ifdef YUNI_OS_DARWIN
		pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
		# else
		pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);
		# endif
		//pthread_mutex_init(&pPthreadLock, &mutexattr);
		*/
		//pthread_mutexattr_destroy(&mutexattr);
		pthread_mutex_init(&pPthreadLock, NULL);
	}

} // namespace Yuni

