#ifndef __YUNI_THREADS_THREAD_TIMER_H__
# define __YUNI_THREADS_THREAD_TIMER_H__

# include "../yuni.h"
# include "mutex.h"
# include "abstract.thread.h"



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
	**	 Timer(int p): Yuni::Thread::Timer() {}
	**	 virtual ~Timer() {stop();} // Absolutely needed
	**
	** protected:
	**	 virtual void execute();
	** };
	**
	** void Timer::execute()
	** {
	**	 for (int i = 0; i < 50; ++i)
	**		std::cout << "Thread " << pTag << ": Do some stuff here" << std::endl;
	** }
	**
	** int main(void)
	** {
	**	 Timer timer;
	**	 timer.timeInterval = 5; // 5 seconds
	**	 job2.wait();
	**	 return 0;
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

		//! \name Time interval
		//@{

		/*!
		** \brief Get the time interval (in `ms`)
		*/
		uint32 timeInterval(); 

		/*!
		** \brief Set the time interval (in `ms`)
		**
		** The change of this value will be taken into consideration at the next pause
		** the timer will make
		**
		** \param t The new time interal in milliseconds
		*/
		void timeInterval(const uint32 t);

		//@}


		//! \name Cycles
		//@{

		/*!
		** \brief Get the maximum number of cycle to execute (0 means infinite)
		*/
		uint32 cycleMax();

		/*!
		** \brief Set the maximum number of cycle to execute
		**
		** This value will only be taken into consideration at the next start of
		** the timer. If you want that the change be done immediately, you have
		** to restart the timer.
		*/
		void cycleMax(const uint32 t);

		//@}


	protected:
		/*!
		** \brief Event: The timer has just been started
		**
		** This event is executed in the thread which has just been created.
		**
		** It can be directly stopped if returning false. However the `onStopped` event
		** will not be called.
		**
		** \return True to continue the execution of the thread, false to abort the
		** execution right now
		*/
		virtual bool onStarting() {return true;}

		/*!
		** \brief Event: Execute a new cycle
		**
		** There is no really need to use suspend() in this method, it will be already
		** done for you.
		**
		** \param cycleCount The current cycle number. Always 0 in the case of an infinite timer 
		** \return True to continue the execution of the timer, False otherwise
		*/
		virtual bool onExecute(const uint32 cycleCount) = 0;

		/*!
		** \brief Event: The timer has been stopped
		**
		** This event is executed in the thread.
		**
		** \attention You should not rely on this event to release your resources. There is no guaranty
		** that this method will be called, especially if the thread has been killed because
		** it did not stop before the timeout was reached.
		*/
		virtual void onStopped() {}


	private:
		//! Calls `onExecute()` each `pTimeInterval` milliseconds
		virtual void baseExecute();

	private:
		//! The time interval
		uint32 pTimeInterval;
		//! The maximum number of cycles before stopping, 0 means infinite
		uint32 pCyclesCount;
		//! The current cycle
		uint32 pCycleCurrent;

	}; // class Thread::Timer




} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_THREAD_TIMER_H__
