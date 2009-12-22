
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


#if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
#	define YUNI_OS_GETPID  _getpid
#else
#	define YUNI_OS_GETPID  getpid
#endif



namespace Yuni
{
namespace Private
{
namespace Thread
{


	extern "C"
	{
		/*!
		** \brief This procedure will be run in a separate thread and will run AThread::baseExecute()
		*/
		void* threadMethodForPThread(void* arg)
		{
			assert(NULL != arg);

			// Adjust cancellation behaviors
			::pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
			::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

			// Get back our object.
			Yuni::Thread::AThread* t = (Yuni::Thread::AThread *) arg;

			assert(false == t->pStarted);

			// Aquire the condition, so that start() cannot continue.
			t->pStartupCond.lock();

			if (t->onStarting())
			{
				// onStarting authorized us to continue. So say we are now running.
				// NOTE: We should not lock pMutex for pStarted here.
				//       The lock on pMutex is held by start(),
				//       and we hold a condition lock on start(), so all is well.
				t->pStarted = true;

				// signal the start() method in the parent thread, then unlock.
				t->pStartupCond.notify();
				t->pStartupCond.unlock();

				// Launch the code
				t->onExecute();

				// The thread has stopped, execute the user's stop handler.
				t->onStopped();

				// We have stopped executing user code, and are exiting.
				// Signal any threads waiting for our termination.
				// NOTE: We should not lock pMutex here, since a lock on it MAY be held by stop().
				//       Instead, we lock pAboutToExitCond. Indeed, stop() will wait for a signal on ExitCond.
				//       while we hold ExitCond, stop(), which waits on ExitCond, holds pMutex.
				t->pAboutToExitCond.lock();
				t->pShouldStop = true;
				t->pStarted = false;
				t->pAboutToExitCond.notify();
				t->pAboutToExitCond.unlock();
			}
			else
			{
				// The startup failed. So, pStarted is left to false.
				// signal the start() method in the parent thread, then unlock.
				t->pStartupCond.notify();
				t->pStartupCond.unlock();
			}

			return NULL;
		}
	}


} // namespace Yuni
} // namespace Private
} // namespace Thread





namespace Yuni
{
namespace Thread
{


	unsigned int AThread::ProcessID()
	{
		return YUNI_OS_GETPID();
	}


	AThread::Error AThread::start()
	{
		ThreadingPolicy::MutexLocker locker(*this);

		// Lock the startup conditon.
		ConditionLocker condLocker(pStartupCond);

		if (pStarted)
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
		if (::pthread_create(&pThreadID, NULL, Yuni::Private::Thread::threadMethodForPThread, this))
		{
			// Thread creation failed, abort.
			return errThreadCreation;
		}

		// Unlock and wait to be signalled by the new thread.
		// This MUST happen.
		pStartupCond.waitUnlocked();
		// The condition is now locked again, our thread has set pStarted according
		// to the selected course of action.

		if (!pStarted)
		{
			// The thread has been aborted by a startup handler.
			return errAborted;
		}

		return errNone;
	}


	AThread::Error AThread::stop(const uint32 timeout)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		// Our thread will be blocked in pAboutToExitCond.notify() if it crosses it.
		pAboutToExitCond.lock();

		// Check the thread status
		if (!pStarted) // already stopped, nothing to do.
		{
			pAboutToExitCond.unlock();
			return errNone;
		}

		// Early indicates that this thread should stop, should it check that value.
		pShouldStop = true;
		// Notify
		pMustStopCond.notifyLocked();

		// Our status
		Error status = errNone;

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
		pStarted = false;

		return status;
	}


	void AThread::wakeUp()
	{
		ThreadingPolicy::MutexLocker locker(*this);

		// Our thread will be blocked in pAboutToExitCond.notify() if it crosses it.
		pAboutToExitCond.lock();

		// Check the thread status
		if (!pStarted) // already stopped, nothing to do.
		{
			pAboutToExitCond.unlock();
			return;
		}

		// Notify
		pMustStopCond.notifyLocked();
		// Release the ExitCondition, so the thread can join us.
		pAboutToExitCond.unlock();
	}


	bool AThread::suspend(const unsigned int delay)
	{
		ConditionLocker locker(pMustStopCond);

		// The thread should stop as soon as possible
		if (pShouldStop)
			return true;
		// If we have not started, why bother to wait...
		if (!pStarted)
			return true;
		// We should rest for a while...
		if (delay)
			pMustStopCond.waitUnlocked((uint32) delay);

		return (pShouldStop || !pStarted);
	}


	void AThread::gracefulStop()
	{
		pMutex.lock();
		pShouldStop = true;
		pMustStopCond.notifyLocked();
		pMutex.unlock();
	}


	AThread::Error AThread::restart(const unsigned int timeout)
	{
		const Error status = stop(timeout);
		return (status != errNone) ? status : start();
	}




} // namespace Thread
} // namespace Yuni

