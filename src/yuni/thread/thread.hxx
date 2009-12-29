#ifndef __YUNI_THREAD_THREAD_HXX__
# define __YUNI_THREAD_THREAD_HXX__

# include <assert.h>


namespace Yuni
{
namespace Thread
{


	inline IThread::IThread()
		:pStarted(false), pShouldStop(true)
	{}


	inline IThread::~IThread()
	{
		assert(pStarted == false && "A thread can not be destroyed while being still started");
	}


	inline bool IThread::started() const
	{
		return pStarted;
	}


	inline bool IThread::shouldAbort()
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
