
#include <yuni/threads/timer.h>
#include <yuni/threads/abstract.thread.h>
#include <assert.h>




namespace Yuni
{
namespace Threads
{

    Timer::Timer()
        :Private::AbstractThreadModel(), pTimeInterval(1000), pCyclesCount(0)
    {}

    Timer::Timer(const uint32 t)
        :Private::AbstractThreadModel(), pTimeInterval(t), pCyclesCount(0)
    {}

    Timer::Timer(const uint32 t, const uint32 c)
        :Private::AbstractThreadModel(), pTimeInterval(t), pCyclesCount(c)
    {}

    Timer::~Timer()
    {
        assert(isRunning() == false);
    }

    void Timer::baseExecute()
    {
        pMutex.lock();
        if (!pCyclesCount)
        {
            pMutex.unlock();
            while(true)
            {
                if (suspend(pTimeInterval) || execute())
                    return;
            }
        }
        else
        {
            pCycleCurrent = 0;
            pMutex.unlock();
            while(true)
            {
                pMutex.lock();
                uint32 nnTimeInterval(pTimeInterval);
                pMutex.unlock();
                if (suspend(nnTimeInterval) || execute())
                    return;
                pMutex.lock();
                ++pCycleCurrent;
                if (pCycleCurrent >= pCyclesCount)
                {
                    pMutex.unlock();
                    return;
                }
                pMutex.unlock();
            }
        }
    }

    uint32 Timer::timeInterval()
    {
        MutexLocker locker(pMutex);
        return pTimeInterval;
    }

    void Timer::timeInterval(const uint32 t)
    {
        pMutex.lock();
        pTimeInterval = t;
        pMutex.unlock();
    }


    uint32 Timer::cycleMax()
    {
        MutexLocker locker(pMutex);
        return pCyclesCount;
    }


    void Timer::cycleMax(const uint32 t)
    {
        pMutex.lock();
        pCycleCurrent = 0;
        pCyclesCount = t;
        pMutex.unlock();
    }


} // namespace Threads
} // namespace Yuni

