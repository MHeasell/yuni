
#include "signal.h"
#include <cassert>

#ifndef YUNI_NO_THREAD_SAFE
# ifdef YUNI_OS_WINDOWS
#	include "../core/system/windows.hdr.h"
# else
#	include <time.h>
#	include <sys/time.h>
#	include <errno.h>
#	include "../core/system/gettimeofday.h"
# endif
#endif


namespace Yuni
{
namespace Thread
{

	Signal::Signal()
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		// Making sure that our pseudo HANDLE type is valid
		assert(sizeof(HANDLE) >= sizeof(void*) && "Invalid type for Signal::pHandle");

		pHandle = (void*) CreateEvent( 
				NULL,     // default security attributes
				TRUE,     // manual-reset event
				FALSE,    // initial state is nonsignaled
				NULL );   // unamed

		# else
		pSignalled = false;
		::pthread_mutex_init(&pMutex, NULL);
		::pthread_cond_init(&pCondition, NULL);
		# endif
		#endif
	}


	Signal::~Signal()
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		CloseHandle(pHandle);
		# else
		::pthread_cond_destroy(&pCondition);
		::pthread_mutex_destroy(&pMutex);
		# endif
		#endif
	}



	bool Signal::reset()
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		return (pHandle && ResetEvent(pHandle));
		# else

		pthread_mutex_lock(&pMutex);
		pSignalled = false;
		pthread_mutex_unlock(&pMutex);
		return true;
		# endif

		#else // NO THREADSAFE
		return true;
		#endif
	}


	void Signal::wait()
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS

		if (pHandle)
			WaitForSingleObject(pHandle, INFINITE);

		# else

		// The pthread_cond_wait will unlock the mutex and wait for
		// signalling.

		int pthread_cond_wait_error;
		pthread_mutex_lock(&pMutex);
		do
		{
			// Spurious wakeups from this function can occur.
			// Therefore we must check out pSignalled variable to ensure we have
			// really been signalled.
			pthread_cond_wait_error = ::pthread_cond_wait(&pCondition, &pMutex);
		} while (pSignalled != true);

		// The condition was signalled: the mutex is now locked again.
		pthread_mutex_unlock(&pMutex);
		# endif

		# else // NO THREADSAFE
		# endif
	}


	bool Signal::wait(unsigned int timeout)
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		if (pHandle)
		{
			switch (WaitForSingleObject(pHandle, static_cast<DWORD>(timeout)))
			{
				case WAIT_OBJECT_0:
					return true;
				default:
					break;
			}
		}
		return false;
		# else

		Yuni::timeval now;
		struct timespec t;

		// Set the timespec t at [timeout] milliseconds in the future.
		assert(timeout < 2147483648u && "Invalid range for timeout (Signal::wait(timeout))");
		YUNI_SYSTEM_GETTIMEOFDAY(&now, NULL);
		t.tv_nsec  =  static_cast<long>  (now.tv_usec * 1000 + ((static_cast<int>(timeout) % 1000) * 1000000));
		t.tv_sec   =  static_cast<time_t>(now.tv_sec + timeout / 1000 + (t.tv_nsec / 1000000000L));
		t.tv_nsec  %= 1000000000L;

		int error;
		pthread_mutex_lock(&pMutex);
		do
		{
			// Avoid spurious wakeups (see waitUnlocked() above for explanations)
			error = ::pthread_cond_timedwait(&pCondition, &pMutex, &t);
		}
		while (pSignalled != true // Condition not verified
			&& error != ETIMEDOUT // We have not timedout
			&& error != EINVAL);  // When t is in the past, we got EINVAL. We consider this as a timeout.

		pthread_mutex_unlock(&pMutex);
		// The condition was signalled or has timeoutted:
		return (pSignalled != false);
		# endif

		# else // NO THREADSAFE
		return true;
		# endif
	}


	bool Signal::notify()
	{
		#ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS

		return (pHandle && SetEvent(pHandle));

		# else

		::pthread_mutex_lock(&pMutex);
		pSignalled = true;
		::pthread_cond_signal(&pCondition);
		::pthread_mutex_unlock(&pMutex);
		return true;

		# endif

		# else // NO THREADSAFE
		return true;
		# endif
	}





} // namespace Thread
} // namespace Yuni
