#ifndef __YUNI_THREADS_PRIVATE_ABSTRACT_H__
# define __YUNI_THREADS_PRIVATE_ABSTRACT_H__

# include <yuni/yuni.h>
# include <yuni/string.h>
# include <yuni/threads/mutex.h>
# include <pthread.h>



namespace Yuni
{
namespace Threads
{
namespace Private
{

	extern "C"
	{
		/*!
		** \brief This procedure will be run in a separate thread and will run AbstractThreadModel::baseExecute()
		*/
		void* threadMethodForPThread(void* arg);
	}




	class AbstractThreadModel
	{
		friend void* threadMethodForPThread(void* arg);
	public:
		/*!
		** \brief Get the number of system CPU, 1 if unknown
		*/
		static int CPUCount();

		/*!
		** \brief Convenient method to create, start and return a new instancied thread
		**
		** \param f True to destroy the thread as soon as it has stopped
		** \return A pointer to the new instance
		*/
		template<class T>
		static T* CreateAndStart(const bool f = false)
		{T* t = new T(); if (f) t->freeOnTerminate(f); t->start(); return t;}


	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		AbstractThreadModel();
		//! Copy constructor
		AbstractThreadModel(const AbstractThreadModel& c);
		//! Destructor
		virtual ~AbstractThreadModel();
		//@}


		/*!
		** \brief Get the name of this thread
		*/
		virtual String name() {return String("<Unknown>");}

		/*!
		** \brief Start the execution of the thread, if not already started
		**
		** This method can be safely called twice or more
		**
		** \return True if the thread has been started
		*/
		bool start();
		
		/*!
		** \brief Stop the exeuction of the thread and wait for it, if not already stopped
		**
		** \param timeout The timeout in seconds before killing the thread
		** \return True if the thread has been stopped
		*/
		bool stop(const uint16 timeout = 5 /* 5 seconds */);

		/*!
		** \brief Announce that the thread should stop as soon as possible
		**
		** All call to `suspend()` in this thread will abort immediately
		*/
		void gracefulStop();

		/*!
		** \brief Get if the thread is currently running
		** \return True if the thread is running
		*/
		bool isRunning() const {return pIsRunning;}

		//! Get if the thread is destroyed as soon as it has stopped
		bool freeOnTerminate();
		//! Set if the thread is destroyed as soon as it has stopped
		void freeOnTerminate(const bool f);

	
		/*!
		** \brief Suspend the execution of the thread of X miliseconds
		**
		** This method should only be called inside the execution of the thread
		**
		** \param delay The delay in miliseconds. O will only return if the thred should exit
		** \return True indicates that the thread should stop immediately
		*/
		bool suspend(uint32 delay);


	protected:
		virtual bool startTimer() = 0;
		/*!
		** \brief This method is reimplemented by the specific thread model
		**
		** The thread will stop as soon as this method returns
		*/
		virtual void baseExecute() = 0;
		virtual void stopTimer() = 0;

	protected:
		//! Mutex
		Mutex pMutex;

	private:
		void signalThreadAboutToExit();
		void internalExecute();

	private:
		//! Mutex to exit
		Mutex p_mutexThreadIsAboutToExit;
		Mutex p_threadMustStopMutex;
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

	}; // class Private::AbstractThreadModel


} // namespace Private
} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_PRIVATE_ABSTRACT_H__
