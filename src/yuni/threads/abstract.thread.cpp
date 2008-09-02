
#include "../yuni.h"
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <assert.h>
#ifndef YUNI_OS_WINDOWS
#	include <sys/errno.h>
#	include <unistd.h>
#	include <sys/time.h>
#else
#	include "../system/windows.hdr.h"
#	include <process.h>
#	include "../system/windows/gettimeofday.h"
#endif

#include "thread.h"
#include "abstract.thread.h"


#if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
#	define YUNI_OS_GETPID  _getpid
#else
#	define YUNI_OS_GETPID  getpid
#endif



namespace Yuni
{
namespace Threads
{
namespace Private
{


	unsigned int AbstractThreadModel::ProcessID()
	{
		return YUNI_OS_GETPID();
	}




	namespace
	{
		/*!
		 * \brief Get a new timespec struct representing X milli seconds in the future 
		 *
		 * \param[in,out] The timespec struct
		 * \param millisecs The count of milli seconds
		 * \return Always `time` itself
		 */
		struct timespec* millisecondsFromNow(struct timespec* time, int millisecs)
		{
			# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
			struct _timeb currSysTime;
			# else
			struct timeb currSysTime;
			# endif
			sint64 nanosecs, secs;
			const sint64 NANOSEC_PER_MILLISEC = 1000000;
			const sint64 NANOSEC_PER_SEC = 1000000000;

			/* get current system time and add millisecs */
			# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
			_ftime_s(&currSysTime);
			# else
			ftime(&currSysTime);
			# endif

			nanosecs = ((sint64) (millisecs + currSysTime.millitm)) * NANOSEC_PER_MILLISEC;
			if (nanosecs >= NANOSEC_PER_SEC)
			{
				secs = currSysTime.time + 1;
				nanosecs %= NANOSEC_PER_SEC;
			}
			else
				secs = currSysTime.time;

			time->tv_nsec = (long)nanosecs;
			time->tv_sec = (long)secs;
			return time;
		}
	}


	extern "C"
	{
		/*!
		 * \brief This procedure will be run in a separate thread and will run AbstractThreadModel::baseExecute()
		 */
		void* threadMethodForPThread(void* arg)
		{
			if (!arg)
				return NULL;
			// PThread stuff
			pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

			AbstractThreadModel* t = (AbstractThreadModel *) arg;
			t->pIsRunning = true;
			if (t->onStarting())
			{
				// Launch the code
				t->baseExecute();
				// The thread has stopped
				t->onStopped();
			}
			t->signalThreadAboutToExit();
			if (t->pFreeOnTerminate)
				delete t;
			return NULL;
		}
	}



	AbstractThreadModel::AbstractThreadModel()
		:pMutex(), pThreadID(), pIsRunning(false), pFreeOnTerminate(false), pShouldStop(true)
	{
		pthread_cond_init(&p_threadMustStopCond, NULL);
		pthread_cond_init(&p_threadIsAboutToExit, NULL);
	}

	AbstractThreadModel::~AbstractThreadModel()
	{
		assert(pIsRunning == false);

		pthread_cond_destroy(&p_threadMustStopCond);
		pthread_cond_destroy(&p_threadIsAboutToExit);
	}

	bool AbstractThreadModel::freeOnTerminate()
	{
		MutexLocker locker(pMutex);
		return pFreeOnTerminate;
	}

	void AbstractThreadModel::freeOnTerminate(const bool f)
	{
		pMutex.lock();
		pFreeOnTerminate = f;
		pMutex.unlock();
	}


	bool AbstractThreadModel::start()
	{
		MutexLocker locker(pMutex);
		if (pIsRunning)
			return true;
		pShouldStop = false;
		pIsRunning = (0 == pthread_create(&pThreadID, NULL, threadMethodForPThread, this));
		return pIsRunning;
	}


	bool AbstractThreadModel::stop(const uint16 timeout)
	{
		MutexLocker locker(pMutex);
		if (!pIsRunning) // already stopped
			return true;

		// Early indicates that this thread should stop
		pShouldStop = true;
		// As we explicitly ask to stop (external call), this class must not destroy itself
		pFreeOnTerminate = false;

		pMutexThreadIsAboutToExit.lock();

		pThreadMustStopMutex.lock();
		pthread_cond_signal(&p_threadMustStopCond);
		pThreadMustStopMutex.unlock();

		if (pIsRunning)
		{
			// The thread is still running

			// Timeout
			struct timeval mytime;
			struct timespec myts;
			gettimeofday(&mytime, NULL);
			myts.tv_sec = mytime.tv_sec + timeout;
			myts.tv_nsec = mytime.tv_usec * 1000;																		

			// Waiting for the end of the thread
			int result = pthread_cond_timedwait(&p_threadIsAboutToExit, &pMutexThreadIsAboutToExit.pthreadMutex(), &myts);
			if (result) // A problem occured, or we timed out.
			{
				// We are out of time, no choice but to kill our thread
				pthread_cancel(pThreadID);
			}
		}

		pMutexThreadIsAboutToExit.unlock();
		// Wait for the thread be completely stopped
		pthread_join(pThreadID, NULL);
		// The thread is no longer running
		pIsRunning = false;
		return true;
	}


	bool AbstractThreadModel::suspend(const uint32 delay)
	{
		MutexLocker locker(pThreadMustStopMutex);
	
		// The thread should stop as soon as possible
		if (pShouldStop) 
			return true;

		// If we have not started, why bother to wait...
		if (!pIsRunning)
			return false; 

		// We should rest for a while...
		if (delay)
		{
			struct timespec ts;
			pthread_cond_timedwait(&p_threadMustStopCond, &pThreadMustStopMutex.pthreadMutex(),
								   millisecondsFromNow(&ts, delay));
		}
		return (pShouldStop || !pIsRunning);
	}


	void AbstractThreadModel::signalThreadAboutToExit()
	{
		pShouldStop = true;
		pIsRunning = false;
		pMutexThreadIsAboutToExit.lock();
		pthread_cond_signal(&p_threadIsAboutToExit);
		pMutexThreadIsAboutToExit.unlock();
	}


	void AbstractThreadModel::gracefulStop()
	{
		MutexLocker locker(pMutex);
		pShouldStop = true;

		pThreadMustStopMutex.lock();
		pthread_cond_signal(&p_threadMustStopCond);
		pThreadMustStopMutex.unlock();
	}



} // namespace Private
} // namespace Threads
} // namespace Yuni

