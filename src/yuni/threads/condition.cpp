
#include "../yuni.h"
#include <time.h>
#if defined(YUNI_OS_MSVC)
# include <winsock2.h>
#else
# include <sys/time.h>
#endif
#include <errno.h>
#include "condition.h"
#include "../core/system/windows/gettimeofday.h"


namespace Yuni
{
namespace Threads
{

	Condition::Condition()
		:pPredicate(false), pOwnMutex(true)
	{
		// Note: The linux implementation currently does not support
		// any condition attr
		::pthread_cond_init(&pCondition, NULL);
		pMutex = new Mutex();
	}


	Condition::Condition(Mutex& mutex)
		:pMutex(&mutex), pPredicate(false), pOwnMutex(false)
	{
		// Note: The linux implementation currently does not support
		// any condition attr
		::pthread_cond_init(&pCondition, NULL);
	}


	Condition::~Condition()
	{
		::pthread_cond_destroy(&pCondition);
		if (pOwnMutex)
			delete pMutex;
	}


	void Condition::wait()
	{
		// The mutex must be locked for the condition
		pMutex->lock();
		// Reset of the predicate
		pPredicate = false;

		// Waiting...
		do
		{
			::pthread_cond_wait(&pCondition, &pMutex->pthreadMutex());
		} while (!pPredicate);

		pPredicate = false;

		// The mutex will remain unlocked. It is the responsability of the user
		// to unlock the mutex
		// pMutex->unlock();
	}


	bool Condition::wait(unsigned int timeout)
	{
		struct timeval now;
		struct timespec t;

		// The mutex must be locked for the condition
		pMutex->lock();
		// Reset of the predicate
		pPredicate = false;

		gettimeofday(&now, NULL);
		t.tv_sec = now.tv_sec + timeout;
		t.tv_nsec = now.tv_usec * 1000;
		int retcode;

		// Waiting...
		do
		{
			retcode = ::pthread_cond_timedwait(&pCondition, &pMutex->pthreadMutex(), &t);
		} while (!pPredicate && retcode != ETIMEDOUT);

		pPredicate = false;

		// The mutex will remain unlocked. It is the responsability of the user
		// to unlock the mutex
		// pMutex->unlock();

		return (retcode == ETIMEDOUT);
	}


	void Condition::unlock()
	{
		pMutex->unlock();
	}


	void Condition::notify()
	{
		pMutex->lock();
		pPredicate = true;
		::pthread_cond_signal(&pCondition);
		pMutex->unlock();
	}


	void Condition::notifyAllThreads()
	{
		pMutex->lock();
		pPredicate = true;
		::pthread_cond_broadcast(&pCondition);
		pMutex->unlock();
	}




} // namespace Threads
} // namespace Yuni


