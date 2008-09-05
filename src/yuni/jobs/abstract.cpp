
#include "abstract.h"
#include "../misc/math.h"


# define YUNI_JOBS_PRIORITY_MIN  -100
# define YUNI_JOBS_PRIORITY_MAX  100



namespace Yuni
{
namespace Jobs
{


	Abstract::Abstract()
		:pMutex(), pName(), pPriority(0), pThread(NULL)
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

	sint8 Abstract::priority()
	{
		MutexLocker locker(pMutex);
		return pPriority;
	}

	void Abstract::priority(const int p)
	{
		pMutex.lock();
		pPriority = Math::MinMax<int>(YUNI_JOBS_PRIORITY_MIN, YUNI_JOBS_PRIORITY_MAX, p);
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
