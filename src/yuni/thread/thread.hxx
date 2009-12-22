#ifndef __YUNI_THREAD_THREAD_HXX__
# define __YUNI_THREAD_THREAD_HXX__

# include <assert.h>


namespace Yuni
{
namespace Thread
{


	inline AThread::AThread()
		:pStarted(false), pShouldStop(true)
	{}


	inline AThread::~AThread()
	{
		assert(pStarted == false && "A thread can not be destroyed while being still started");
	}


	inline bool AThread::started() const
	{
		return pStarted;
	}


	inline bool AThread::shouldAbort()
	{
		ConditionLocker locker(pMustStopCond);
		return (pShouldStop || !pStarted);
	}



	template<class T> inline T* CreateAndStart()
	{
		T* thread = new T();
		thread->start();
		return thread;
	}




} // namespace Thread
} // namespace Yuni

#endif // __YUNI_THREAD_THREAD_HXX__
