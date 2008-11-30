
#include "abstract.h"
#include "../toolbox/math.h"




namespace Yuni
{
namespace Jobs
{


	Abstract::Abstract()
		:pMutex(), pState(jsIdle), pName(), pProgression(0.0f), pThread(NULL)
	{}

	Abstract::~Abstract()
	{}



	String Abstract::name()
	{
		MutexLocker locker(pMutex);
		return pName;
	}

	void Abstract::name(const String& n)
	{
		pMutex.lock();
		pName = n;
		pMutex.unlock();
	}

	
	void Abstract::attachToThread(Threads::Private::AbstractThreadModel* t)
	{
		pMutex.lock();
		pThread = t;
		pMutex.unlock();
	}

	Threads::Private::AbstractThreadModel* Abstract::attachedThread()
	{
		MutexLocker locker(pMutex);
		return pThread;
	}


	bool Abstract::suspend(const uint32 delay)
	{
		pMutex.lock();
		if (pThread && jsRunning == pState)
		{
			Threads::Private::AbstractThreadModel* t(pThread);
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


	void Abstract::progression(const float p)
	{
		pMutex.lock();
		pProgression = p;
		pMutex.unlock();
	}


	State Abstract::state()
	{
		MutexLocker locker(pMutex);
		return pState;
	}


	void Abstract::execute()
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
