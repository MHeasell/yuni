#ifndef __YUNI_THREAD_THREAD_H__
# define __YUNI_THREAD_THREAD_H__

# include "../yuni.h"
# include "mutex.h"
# include "condition.h"
# include "../core/string.h"
# include <vector>


namespace Yuni
{
namespace Job
{

	// forward declaration
	class IJob;

} // namespace Job
} // namespace Yuni



namespace Yuni
{
namespace Thread
{

	/*!
	** \brief Get the current process ID
	*/
	unsigned int ProcessID();



	/*!
	** \brief Convenient method to create, start and return a new instancied thread
	**
	** The user is responsible for releasing it.
	** \code
	** class MyOwnThread : public Yuni::Threads::IThread
	** {
	** public:
	**   MyOwnThread(int p): Yuni::Threads::IThread(), pTag(p)  {}
	**   virtual ~MyOwnThread() {stop();} // Required for Code robustness
	**
	** protected:
	**   virtual void onExecute()
	**   {
	**      for (int i = 0; i < 50; ++i)
	**         std::cout << "Thread " << pTag << ": Do some stuff here" << std::endl;
	**   }
	**
	** private:
	**   int pTag;
	** };
	**
	** int main(void)
	** {
	**    // Fire-and-forget our new thread
	**    Yuni::Thread::CreateAndStart<MyOwnThread>();
	**
	**    // Do some other stuff here...
	** }
	** \endcode
	**
	** \tparam T A descendant of the class Yuni::Thread::IThread
	** \return A pointer to the new instance
	*/
	template<class T> T* CreateAndStart();




	/*!
	** \brief Internal Base class interface for Threads (abstract)
	**
	** The thread is really created when started (with the method start()), and
	** destroyed when stopped by the method stop() (or when the object is
	** destroyed too).
	*/
	class IThread : public Policy::ObjectLevelLockable<IThread>
	{
	public:
		//! The threading policy
		typedef Policy::ObjectLevelLockable<IThread>  ThreadingPolicy;
		//! The most suitable smart pointer for the class
		typedef SmartPtr<IThread> Ptr;

		//! Return error status
		enum Error
		{
			//! The operation failed for an unkown reason
			errUnkown = 0,
			//! No error, the operation succeeded
			errNone = 1,
			//! A timeout occured
			errTimeout,
			//! Impossible to create the new thread
			errThreadCreation,
			//! The onStarting handler returned false.
			errAborted
		};
		enum
		{
			//! The default timeout for stopping a thread
			defaultTimeout = 5000, // 5 seconds
		};


	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		IThread();
		//! Destructor
		virtual ~IThread();
		//@}


		//! \name Execution flow
		//@{
		/*!
		** \brief Start the execution of the thread, if not already started
		**
		** If already started, the thread will be woke up
		** \return True if the thread has been started
		*/
		Error start();

		/*!
		** \brief Stop the execution of the thread and wait for it, if not already stopped
		**
		** \param timeout The timeout in milliseconds before killing the thread (default: 5000ms)
		** \return An error status (`errNone` if succeeded)
		*/
		Error stop(const uint32 timeout = defaultTimeout);

		/*!
		** \brief Wait for an infinite amount of time for the end of the thread
		**
		** The thread is not stopped during the process.
		** \return An error status (`errNone` if succeeded)
		*/
		Error wait();

		/*!
		** \brief Wait for the end of the thread
		**
		** The thread is not stopped during the process.
		** \param timeout The timeout in milliseconds
		** \return An error status (`errNone` if succeeded)
		*/
		Error wait(const uint32 timeout);

		/*!
		** \brief Restart the thread
		**
		** \param timeout The timeout in milliseconds before killing the thread (default: 5000ms)
		** \return True if the thread has been stopped then started
		**
		** \see stop()
		** \see start()
		*/
		Error restart(const unsigned int timeout = defaultTimeout);

		/*!
		** \brief Ask to Stop the execution of the thread as soon as possible
		**
		** After a call to this method, the method suspend() will return true,
		** which indicates that the thread should stop.
		** \see suspend()
		*/
		void gracefulStop();

		/*!
		** \brief Get if the thread is currently running
		** \return True if the thread is running
		*/
		bool started() const;

		/*!
		** \brief Interrupt the thread if suspended
		**
		** A call to this methid will interrupt a suspended state.
		** This method has no effect if the thread is not started.
		*/
		void wakeUp();
		//@}


	protected:
		/*!
		** \brief Suspend the execution of the thread of X miliseconds
		**
		** This is a convenient method to know if the thread should stop as soon as possible.
		** If you do not want to suspend the execution of thread, you should use the
		** method `shouldAbort()` instead.
		**
		** \attention This method must only be called inside the execution of the thread
		**
		** \param delay The delay in miliseconds. O will only return if the thread should exit
		** \return True indicates that the thread should stop immediately
		*/
		bool suspend(const unsigned int delay = 0);

		/*!
		** \brief Get if the thread should abort as soon as possible
		**
		** This is a convenient routine instead of `suspend(0)`, but a bit faster.
		** \attention This method must only be called inside the execution of the thread
		** \return True indicates that the thread should stop immediately
		*/
		bool shouldAbort();

		/*!
		** \brief Event: The thread has just been started
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
		** \brief Event: The thread is running
		**
		** The thread has been successfully started (and `onStarting()` returned true).
		**
		** If this method returns false, the thread will be stopped (and the thread
		** context will be destroyed). The method `onStopped` will be called.
		** Otherwise, the thread will be paused for an infinite amount of time and the
		** method onPause() will be called. In this case it will be possible to re-run it
		** in calling wakeUp() or start().
		**
		** \attention This method should check from time to time if the thread has to stop. For that,
		** a call to `suspend(0)` is recommended.
		** \code
		**    if (suspend())
		**       return;
		** \endcode
		**
		** \return True to pause the thread and wait a `wake up` signal, False to effectively stop it.
		** \see suspend()
		** \see onStarting()
		** \see onStopped()
		** \see wakeUp()
		*/
		virtual bool onExecute() = 0;

		/*!
		** \brief Event: The thread has finished its job and is waiting for being re-executed
		**
		** This event will be fired if the method onExecute returns false.
		*/
		virtual void onPause() {}

		/*!
		** \brief Event: The thread has been gracefully stopped
		**
		** This event is executed in the thread.
		**
		** \attention You should not rely on this event to release your resources. There is no guaranty
		** that this method will be called, especially if the thread has been killed because
		** it did not stop before the timeout was reached.
		*/
		virtual void onStop() {}

		/*!
		** \brief Event: The thread has been killed
		**
		** This method may be called from any thread
		*/
		virtual void onKill() {}

	private:
		//! Private copy constructor
		IThread(const IThread&) :ThreadingPolicy() {/* not copyable */}
		//! Operator =
		IThread& operator = (const IThread&) {return *this;}


	private:
		//! Condition used in the startup process. See start().
		Condition pStartupCond;
		//! Condition for exiting
		Condition pAboutToExitCond;
		//! Condition for stopping
		Condition pMustStopCond;
		//! ID of the thread, for pthread
		pthread_t pThreadID;

		//! Get if the thread is running
		volatile bool pStarted;
		//! Should stop the thread ?
		volatile bool pShouldStop;

		// our friend
		friend class Yuni::Job::IJob;
		friend void* Yuni::Private::Thread::threadMethodForPThread(void* arg);

	}; // class IThread





} // namespace Thread
} // namespace Yuni

# include "thread.hxx"

#endif // __YUNI_THREAD_THREAD_H__
