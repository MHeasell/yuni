
#include <yuni/threads/thread.h>
#include <yuni/threads/abstract.thread.h>
#include <time.h>
#include <sys/errno.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>




namespace Yuni
{
namespace Threads
{
namespace Private
{

    namespace
    {
        struct timespec* millisecondsFromNow(struct timespec* time, int millisecs)
        {
            # ifdef YUNI_OS_WINDOWS
            struct _timeb currSysTime;
            # else
            struct timeb currSysTime;
            # endif
            sint64 nanosecs, secs;
            const sint64 NANOSEC_PER_MILLISEC = 1000000;
            const sint64 NANOSEC_PER_SEC = 1000000000;

            /* get current system time and add millisecs */
            # ifdef YUNI_OS_WINDOWS
            _ftime(&currSysTime);
            # else
            ftime(&currSysTime);
            # endif

            nanosecs = ((sint64) (millisecs + currSysTime.millitm)) * NANOSEC_PER_MILLISEC;
            if (nanosecs >= NANOSEC_PER_SEC)
            {
                secs = currSysTime.time + 1;
                nanosecs %= NANOSEC_PER_SEC;
            }
            else
                secs = currSysTime.time;

            time->tv_nsec = (long)nanosecs;
            time->tv_sec = (long)secs;
            return time;
        }
    }


    extern "C"
    {
        /*!
         * \brief This procedure will be run in a separate thread and will run AbstractThreadModel::baseExecute()
         */
        void* threadMethodForPThread(void* arg)
        {
            if (!arg)
                return NULL;
            // PThread stuff
            pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

            AbstractThreadModel* t = (AbstractThreadModel *) arg;
            t->pIsRunning = true;
            if (!t->startTimer())
            {
                // Launch the code
                t->internalExecute();
                // The thread has stopped
                t->stopTimer();
            }
            t->signalThreadAboutToExit();
            if (t->pFreeOnTerminate)
                delete t;
            return NULL;
        }
    }


    AbstractThreadModel::AbstractThreadModel(const AbstractThreadModel&)
        :pMutex(), pThreadID(0), pIsRunning(false), pFreeOnTerminate(false), pShouldStop(true)
    {
        pthread_cond_init(&p_threadMustStopCond, NULL);
        pthread_cond_init(&p_threadIsAboutToExit, NULL);
    }


    AbstractThreadModel::AbstractThreadModel()
        :pMutex(), pThreadID(0), pIsRunning(false), pFreeOnTerminate(false), pShouldStop(true)
    {
        pthread_cond_init(&p_threadMustStopCond, NULL);
        pthread_cond_init(&p_threadIsAboutToExit, NULL);
    }

    AbstractThreadModel::~AbstractThreadModel()
    {
        assert(pIsRunning == false);

        pthread_cond_destroy(&p_threadMustStopCond);
        pthread_cond_destroy(&p_threadIsAboutToExit);
    }

    bool AbstractThreadModel::freeOnTerminate()
    {
        MutexLocker locker(pMutex);
        return pFreeOnTerminate;
    }

    void AbstractThreadModel::freeOnTerminate(const bool f)
    {
        pMutex.lock();
        pFreeOnTerminate = f;
        pMutex.unlock();
    }


    bool AbstractThreadModel::start()
    {
        MutexLocker locker(pMutex);
        if (pIsRunning)
            return true;
        pShouldStop = false;
        pIsRunning = (0 == pthread_create(&pThreadID, NULL, threadMethodForPThread, this));
        return pIsRunning;
    }

    bool AbstractThreadModel::stop(const uint16 timeout)
    {
        MutexLocker locker(pMutex);
        if (!pIsRunning)
            return true;
        pShouldStop = true;
        pFreeOnTerminate = false;

        p_mutexThreadIsAboutToExit.lock();

        p_threadMustStopMutex.lock();
        pthread_cond_signal(&p_threadMustStopCond);
        p_threadMustStopMutex.unlock();

        struct timeval mytime;
        struct timespec myts;

        gettimeofday(&mytime, NULL);
        myts.tv_sec = mytime.tv_sec + timeout;
        myts.tv_nsec = mytime.tv_usec * 1000;                                                                        

        if (pIsRunning)
        {
            int result = pthread_cond_timedwait(&p_threadIsAboutToExit, &p_mutexThreadIsAboutToExit.pthreadMutex(), &myts);
            if (result) // A problem occured, or we timed out.
                pthread_cancel(pThreadID);
        }

        p_mutexThreadIsAboutToExit.unlock();
        pthread_join(pThreadID, NULL);
        pIsRunning = false;
        return true;
    }


    bool AbstractThreadModel::suspend(uint32 delay)
    {
        MutexLocker locker(p_threadMustStopMutex);
        if (pShouldStop)
            return true;
        if (!pIsRunning)
            return false; // If we have not started, why bother to wait..                                        

        if (delay)
        {
            struct timespec ts;
            pthread_cond_timedwait(&p_threadMustStopCond, &p_threadMustStopMutex.pthreadMutex(),
                                   millisecondsFromNow(&ts, delay));
        }
        return (pShouldStop || !pIsRunning);
    }

    void AbstractThreadModel::signalThreadAboutToExit()
    {
        pShouldStop = true;
        pIsRunning = false;
        p_mutexThreadIsAboutToExit.lock();
        pthread_cond_signal(&p_threadIsAboutToExit);
        p_mutexThreadIsAboutToExit.unlock();
    }


    void AbstractThreadModel::gracefulStop()
    {
        MutexLocker locker(pMutex);
        pShouldStop = true;

        p_threadMustStopMutex.lock();
        pthread_cond_signal(&p_threadMustStopCond);
        p_threadMustStopMutex.unlock();
    }


    void AbstractThreadModel::internalExecute()
    {
        baseExecute();
    }


} // namespace Private
} // namespace Threads
} // namespace Yuni

