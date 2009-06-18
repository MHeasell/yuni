#ifndef __YUNI_THREADS_PRIVATE_ABSTRACT_H__
# define __YUNI_THREADS_PRIVATE_ABSTRACT_H__

# include "../yuni.h"
# include "mutex.h"
# include "../core/string.h"



namespace Yuni
{
namespace Threads
{
namespace Private
{

	extern "C"
	{
		/*!
		** \brief This procedure will be run in a separate thread and will run AThreadModel::baseExecute()
		*/
		void* threadMethodForPThread(void* arg);
	}




	/*!
	** \brief Internal Base class interface for Threads (abstract)
	**
	** \attention This class should not be directly used
	*/
	class AThreadModel
	{
		friend void* threadMethodForPThread(void* arg);
	public:
		/*!
		** \brief Get the number of system CPU, 1 if unknown
		*/
		static int CPUCount();

		/*!
		** \brief Get the current process ID
		*/
		static unsigned int ProcessID();

		/*!
		** \brief Convenient method to create, start and return a new instancied thread
		**
		** \code
		** class MyOwnThread : public Yuni::Threads::AThread
		** {
		** public:
		**   MyOwnThread(int p): Yuni::Threads::AThread(), pTag(p)  {}
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
		**    Yuni::Threads::CreateAndStart<MyOwnThread>(true);
		**
		**    // Do some other stuff here...
		** }
		** \endcode
		**
		** \tparam T A descendant of the class Yuni::Private::AThreadModel
		** \param f True to destroy the thread as soon as it has stopped
		** \return A pointer to the new instance
		*/
		template<class T> static T* CreateAndStart(const bool f = false);


	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		AThreadModel();
		//! Destructor
		virtual ~AThreadModel();
		//@}


		/*!
		** \brief Get the name of this thread
		**
		** It is a good practice to provide the name of the thread. This name
		** will be used to show informations at runtime about all running threads
		**
		** \internal This method can not be `const` because it might have to lock the
		** mutex to generate the returned value (in the case of a job for example)
		*/
		virtual String name();


		//! \name Execution flow
		//@{

		/*!
		** \brief Start the execution of the thread, if not already started
		**
		** \return True if the thread has been started
		*/
		bool start();

		/*!
		** \brief Stop the exeuction of the thread and wait for it, if not already stopped
		**
		** \param timeout The timeout in seconds before killing the thread (default: 5s)
		** \return True if the thread has been stopped, or was already stopped
		*/
		bool stop(const uint16 timeout = 5 /* 5 seconds */);

		/*!
		** \brief Restart the thread
		**
		** \param timeout The timeout in seconds before killing the thread (default: 5s)
		** \return True if the thread has been stopped then started
		**
		** \see stop()
		** \see start()
		*/
		bool restart(const uint16 timeout = 5);

		/*!
		** \brief Indicates that the thread should stop as soon as possible
		**
		** \see suspend()
		*/
		void gracefulStop();

		/*!
		** \brief Get if the thread is currently running
		** \return True if the thread is running
		*/
		bool isRunning() const;

		/*!
		** \brief Suspend the execution of the thread of X miliseconds
		**
		** This is a convenient method to know if the thread should stop as soon as possible
		**
		** \attention This method must only be called inside the execution of the thread
		**
		** \param delay The delay in miliseconds. O will only return if the thred should exit
		** \return True indicates that the thread should stop immediately
		*/
		bool suspend(const uint32 delay = 0);

		//@} Execution flow



		//! Get if the thread must be destroyed as soon as it has stopped
		bool freeOnTerminate();
		//! Set if the thread must be destroyed as soon as it has stopped
		void freeOnTerminate(const bool f);


	protected:
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
		virtual bool onStarting() = 0;

		/*!
		** \brief This method is reimplemented by the specific thread model
		**
		** The thread will stop as soon as this method returns
		**
		** \internal This method should be moved to the private scope as soon as possible
		*/
		virtual void baseExecute() = 0;

		/*!
		** \brief Event: The thread has been gracefully stopped
		**
		** This event is executed in the thread.
		**
		** \attention You should not rely on this event to release your resources. There is no guaranty
		** that this method will be called, especially if the thread has been killed because
		** it did not stop before the timeout was reached.
		*/
		virtual void onStopped() = 0;

	protected:
		//! Mutex
		Mutex pMutex;

	private:
		void signalThreadAboutToExit();

	private:
		//! Mutex for exiting
		Mutex pMutexThreadIsAboutToExit;
		//! Mutex for stopping the thread
		Mutex pThreadMustStopMutex;
		//! ID of the thread
		pthread_t pThreadID;
		//! Get if the thread is running
		bool pIsRunning;
		//! Release itself when the thread stops
		bool pFreeOnTerminate;
		//! Should stop the thread ?
		bool pShouldStop;

		pthread_cond_t p_threadMustStopCond;
		pthread_cond_t p_threadIsAboutToExit;

	}; // class Private::AThreadModel





} // namespace Private
} // namespace Threads
} // namespace Yuni

# include "abstract.thread.hxx"

#endif // __YUNI_THREADS_PRIVATE_ABSTRACT_H__
