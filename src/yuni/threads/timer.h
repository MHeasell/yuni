#ifndef __YUNI_THREADS_THREAD_TIMER_H__
# define __YUNI_THREADS_THREAD_TIMER_H__

# include <yuni/yuni.h>
# include <yuni/threads/mutex.h>
# include <yuni/threads/abstract.thread.h>



namespace Yuni
{
namespace Threads
{


    /*!
    ** \brief A thread that execute a method each X seconds
    **
    **
    ** \code
    ** class Timer : public Yuni::Thread::Timer
    ** {
    ** public:
    **     Timer(int p): Yuni::Thread::Timer() {}
    **     virtual ~Timer() {stop();} // Absolutely needed
    **
    ** protected:
    **     virtual void execute();
    ** };
    **
    ** void Timer::execute()
    ** {
    **     for (int i = 0; i < 50; ++i)
    **        std::cout << "Thread " << pTag << ": Do some stuff here" << std::endl;
    ** }
    **
    ** int main(void)
    ** {
    **     Timer timer;
    **     timer.timeInterval = 5; // 5 seconds
    **     job2.wait();
    **     return 0;
    ** }
    ** \endcode
    */
    class Timer : public Private::AbstractThreadModel
    {
    public:
        //! \name Constructor & Destructor
        //@{
        //! Default constructor
        Timer();
        //! Constructor with a time interval
        Timer(const uint32 t);
        //! Constructor with a time interval + cycle count
        Timer(const uint32 t, const uint32 c);
        //! Destructor
        virtual ~Timer();
        //@}

        //! Get the time interval (in `ms`)
        uint32 timeInterval(); 
        //! Set the time interval (in `ms`)
        void timeInterval(const uint32 t);

        //! Get the maximum number of cycle to execute (0 means infinite)
        uint32 cycleMax();
        /*!
        ** \brief Set the maximum number of cycle to execute
        */
        void cycleMax(const uint32 t);

    protected:
        virtual void baseExecute();

        virtual bool startTimer() {return false;}
        /*!
        ** \brief Code to execute when the thread is running
        ** \return True to stop the execution of the thread
        */
        virtual bool execute() = 0;
        virtual void stopTimer() {}

    private:
        //! The time interval
        uint32 pTimeInterval;
        //! The maximum number of cycles before stopping, 0 means infinite
        uint32 pCyclesCount;
        uint32 pCycleCurrent;

    }; // class Thread::Timer




} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_THREAD_TIMER_H__
