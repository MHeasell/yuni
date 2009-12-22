
#include "job.h"
#include "../core/math.h"




namespace Yuni
{
namespace Job
{



	bool IJob::suspend(const unsigned int delay)
	{
		if (stateRunning == pState) // `==` and not `&`
		{
			pMutex.lock();
			if (pThread)
			{
				Thread::AThread* t = pThread;
				pMutex.unlock();
	
				// Really suspend the thread
				pState = stateSleeping | stateRunning;
				const bool sRet = t->suspend(delay);
				pState = stateRunning;
				return sRet;
			}
			pMutex.unlock();
		}
		return true;
	}


	bool IJob::shouldAbort()
	{
		if (stateRunning & pState)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			return (pThread) ? pThread->shouldAbort() : true;
		}
		return true;
	}



	void IJob::execute()
	{
		// Reseting data
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pProgression = 0.f;
			pState = stateRunning;
		}

		// Execute the specific implementation of the job
		onExecute();

		// The job has finished
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pState = stateIdle;
			pProgression = 1.f;
		}
	}




} // namespace Job
} // namespace Yuni

