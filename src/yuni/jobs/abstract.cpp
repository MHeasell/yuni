
#include "abstract.h"
#include "../misc/math.h"




namespace Yuni
{
namespace Jobs
{


	Abstract::Abstract()
		:pMutex(), pName(), pPriority(prNormal), pThread(NULL)
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

	Priority Abstract::priority()
	{
		MutexLocker locker(pMutex);
		return pPriority;
	}

	void Abstract::priority(const Priority p)
	{
		pMutex.lock();
		pPriority = p;
		pMutex.unlock();
	}

	
	void Abstract::attachToThread(Threads::Private::AbstractThreadModel* t)
	{
		pMutex.lock();
		pThread = t;
		pMutex.unlock();
	}


	bool Abstract::suspend(const uint32 delay)
	{
		return (pThread) ? pThread->suspend(delay) : false;
	}



} // namespace Jobs
} // namespace Yuni
