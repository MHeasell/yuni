#ifndef __YUNI_THREAD_TIMER_HXX__
# define __YUNI_THREAD_TIMER_HXX__


namespace Yuni
{
namespace Thread
{


	inline Timer::Timer()
		:AThread(), pTimeInterval(defaultInterval), pCycleCount(infinite)
	{}


	inline Timer::Timer(const unsigned int interval)
		:AThread(), pTimeInterval(interval), pCycleCount(infinite)
	{}


	inline Timer::Timer(const unsigned int interval, const unsigned int cycles)
		:AThread(), pTimeInterval(interval), pCycleCount(cycles)
	{}


	inline Timer::~Timer()
	{
		assert(started() == false);
	}


	inline unsigned int Timer::interval() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pTimeInterval;
	}


	inline unsigned int Timer::cycleCount() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pCycleCount;
	}


	inline void Timer::reload()
	{
		pShouldReload = 1;
	}


} // namespace Thread
} // namespace Yuni

#endif // __YUNI_THREAD_TIMER_HXX__
