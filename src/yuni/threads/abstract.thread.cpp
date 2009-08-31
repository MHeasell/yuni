
#include "../yuni.h"
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <assert.h>
#ifndef YUNI_OS_WINDOWS
#	ifndef YUNI_OS_HAIKU
#		include <sys/errno.h>
#	endif
#	include <unistd.h>
#	include <sys/time.h>
#else
#	include "../core/system/windows.hdr.h"
#	include <process.h>
#	include "../core/system/windows/gettimeofday.h"
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


	unsigned int AThreadModel::ProcessID()
	{
		return YUNI_OS_GETPID();
	}

	extern "C"
	{
		/*!
		** \brief This procedure will be run in a separate thread and will run AThreadModel::baseExecute()
		*/
		void* threadMethodForPThread(void* arg)
		{
			assert(NULL != arg);

			// Adjust cancellation behaviors
			::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
			::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

			// Get back our object.
			AThreadModel* t = (AThreadModel *) arg;

			assert(false == t->pIsRunning);

			// Aquire the condition, so that start() cannot continue.
			t->pStartupCond.lock();

			if (t->onStarting())
			{
				// onStarting authorized us to continue. So say we are now running.
				// NOTE: We should not lock pMutex for pIsRunning here.
				//       The lock on pMutex is held by start(),
				//       and we hold a condition lock on start(), so all is well.
				t->pIsRunning = true;

				// signal the start() method in the parent thread, then unlock.
				t->pStartupCond.notify();
				t->pStartupCond.unlock();

				// Launch the code
				t->baseExecute();

				// The thread has stopped, execute the user's stop handler.
				t->onStopped();
	
				// We have stopped executing user code, and are exiting.
				// Signal any threads waiting for our termination.
				// NOTE: We should not lock pMutex here, since a lock on it MAY be held by stop().
				//       Instead, we lock pAboutToExitCond. Indeed, stop() will wait for a signal on ExitCond.
				//       while we hold ExitCond, stop(), which waits on ExitCond, holds pMutex.
				t->pAboutToExitCond.lock();
				t->pShouldStop = true;
				t->pIsRunning = false;
				t->pAboutToExitCond.notify();
				t->pAboutToExitCond.unlock();
			}
			else
			{
				// The startup failed. So, pIsRunning is left to false.
				// signal the start() method in the parent thread, then unlock.
				t->pStartupCond.notify();
				t->pStartupCond.unlock();
			}

			return NULL;
		}
	}



	AThreadModel::AThreadModel()
		:pIsRunning(false), pShouldStop(true)
	{
	}

	AThreadModel::~AThreadModel()
	{
		assert(pIsRunning == false);
	}

	AThreadModel::Error AThreadModel::start()
	{
		MutexLocker locker(pMutex);

		// Lock the startup conditon.
		ConditionLocker condLocker(pStartupCond);

		if (pIsRunning)
		{
			// The thread is already running, bail out.
			return errNone;
		}

		// We're starting, so we should not stop too soon :)
		pShouldStop = false;

		// Lock the startup condition before creating the thread,
		// then wait for it. The thread will signal the condition when it
		// successfully have set isRunning _and_ called the triggers.
		// Then we can check the isRunning status and determine if the startup
		// was a success or not.
		if (::pthread_create(&pThreadID, NULL, threadMethodForPThread, this))
		{
			// Thread creation failed, abort.
			return errThreadCreation;
		}

		// Unlock and wait to be signalled by the new thread.
		// This MUST happen.
		pStartupCond.waitUnlocked();
		// The condition is now locked again, our thread has set pIsRunning according
		// to the selected course of action.

		if (!pIsRunning)
		{
			// The thread has been aborted by a startup handler.
			return errAborted;
		}
		
		return errNone;
	}


	AThreadModel::Error AThreadModel::stop(const uint32 timeout)
	{
		MutexLocker locker(pMutex);
		Error status = errNone;

		// Our thread will be blocked in pAboutToExitCond.notify() if it crosses it.
		pAboutToExitCond.lock();

		// Check the thread status
		if (!pIsRunning) // already stopped, nothing to do.
		{
			pAboutToExitCond.unlock();
			return errNone;
		}

		// Early indicates that this thread should stop, should it check that value.
		pShouldStop = true;

		// Notify
		pMustStopCond.notifyLocked();

			
		if (pAboutToExitCond.waitUnlocked(timeout)) // We timed out.
		{
			// We are out of time, no choice but to kill our thread
			::pthread_cancel(pThreadID);
			status = errTimeout;
		}

		// Release the ExitCondition, so the thread can join us.
		pAboutToExitCond.unlock();

		// Wait for the thread be completely stopped
		::pthread_join(pThreadID, NULL);

		// The thread is no longer running, force status to stopped (ie, if we killed it)
		// It is thread-safe, since the thread is not running anymore AND we hold pMutex.
		pIsRunning = false;

		return status;
	}


	bool AThreadModel::suspend(const uint32 delay)
	{
		ConditionLocker locker(pMustStopCond);

		// The thread should stop as soon as possible
		if (pShouldStop)
			return true;

		// If we have not started, why bother to wait...
		if (!pIsRunning)
			return false;

		// We should rest for a while...
		if (delay)
			pMustStopCond.waitUnlocked(delay);

		return (pShouldStop || !pIsRunning);
	}

	void AThreadModel::gracefulStop()
	{
		MutexLocker locker(pMutex);

		pShouldStop = true;
		pMustStopCond.notifyLocked();
	}


	AThreadModel::Error AThreadModel::restart(const uint32 timeout)
	{
		const Error status = stop(timeout);
		return (status != errNone) ? status : start();
	}


} // namespace Private
} // namespace Threads
} // namespace Yuni

