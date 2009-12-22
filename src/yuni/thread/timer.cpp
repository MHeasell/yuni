
#include "timer.h"
#include <assert.h>




namespace Yuni
{
namespace Thread
{


	Timer::Timer(const Timer& rhs)
		:AThread()
	{
		rhs.pMutex.lock();
		pTimeInterval = rhs.pTimeInterval;
		pCycleCount = rhs.pCycleCount;
		rhs.pMutex.unlock();
	}


	Timer& Timer::operator = (const Timer& rhs)
	{
		pMutex.lock();
		rhs.pMutex.lock();
		pTimeInterval = rhs.pTimeInterval;
		pCycleCount = rhs.pCycleCount;
		pMutex.unlock();
		rhs.pMutex.unlock();
		return *this;
	}




	bool Timer::internalRunInfiniteLoop()
	{
		const unsigned int nnTimeInterval(pTimeInterval);
		pMutex.unlock();

		while (true)
		{
			if (suspend(nnTimeInterval) || !onInterval(0))
				return true;
			if (pShouldReload)
				return false;
		}
		return true;
	}


	bool Timer::internalRunFixedNumberOfCycles()
	{
		unsigned int cycleIndex = 0;
		const unsigned int nnTimeInterval = pTimeInterval;
		pMutex.unlock();

		while (true)
		{
			// Wait then execute the timer
			if (suspend(nnTimeInterval) || !onInterval(cycleIndex))
				return true;
			if (++cycleIndex >= pCycleCount) // the maximum number of cycle is reached
				return true;
			if (pShouldReload)
				return false;
		}
		return true;
	}


	void Timer::onExecute()
	{
		pShouldReload = 0;
		while (true)
		{
			// Lock
			pMutex.lock();

			// No cycle to do, aborting now
			if (!pCycleCount)
			{
				pMutex.unlock();
				return;
			}

			// infinite loop
			if (infinite == pCycleCount)
			{
				if (internalRunInfiniteLoop())
					return;
			}
			else
			{
				if (internalRunFixedNumberOfCycles())
					return;
			}
		}
	}



	void Timer::interval(const unsigned int t)
	{
		pMutex.lock();
		pTimeInterval = t;
		pMutex.unlock();
	}


	void Timer::cycleCount(const unsigned int n)
	{
		pMutex.lock();
		pCycleCount = n;
		pMutex.unlock();
	}


	void Timer::reload(unsigned int interval, unsigned int cycles)
	{
		pMutex.lock();
		pTimeInterval = interval;
		pCycleCount = cycles;
		pMutex.unlock();
		pShouldReload = 1;
	}




} // namespace Thread
} // namespace Yuni

