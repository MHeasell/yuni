
#include "job.h"
#include "../toolbox/math.h"




namespace Yuni
{
namespace Jobs
{


	AJob::AJob()
		:pMutex(), pState(jsIdle), pName(), pProgression(0.0f), pThread(NULL)
	{}

	AJob::~AJob()
	{}



	String AJob::name()
	{
		MutexLocker locker(pMutex);
		return pName;
	}

	void AJob::name(const String& n)
	{
		pMutex.lock();
		pName = n;
		pMutex.unlock();
	}

	
	void AJob::attachToThread(Threads::Private::AThreadModel* t)
	{
		pMutex.lock();
		pThread = t;
		pMutex.unlock();
	}

	Threads::Private::AThreadModel* AJob::attachedThread()
	{
		MutexLocker locker(pMutex);
		return pThread;
	}


	bool AJob::suspend(const uint32 delay)
	{
		pMutex.lock();
		if (pThread && jsRunning == pState)
		{
			Threads::Private::AThreadModel* t(pThread);
			pState = jsSleeping;
			pMutex.unlock();
			bool sRet = t->suspend(delay);
			
			pMutex.lock();
			pState = jsRunning;
			pMutex.unlock();
			return sRet;
		}
		pMutex.unlock();
		return false;
	}


	void AJob::progression(const float p)
	{
		pMutex.lock();
		pProgression = p;
		pMutex.unlock();
	}


	State AJob::state()
	{
		MutexLocker locker(pMutex);
		return pState;
	}


	void AJob::execute()
	{
		// Lock
		pMutex.lock();
		// Reset some data
		pProgression = 0;
		pState = jsRunning;
		// Unlock
		pMutex.unlock();

		// Execute the specific implementation of the job
		onExecute();

		// The job has finished
		pMutex.lock();
		pState = jsIdle;
		pMutex.unlock();
	}



} // namespace Jobs
} // namespace Yuni
