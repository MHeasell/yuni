#ifndef __YUNI_JOB_AJOB_H__
# define __YUNI_JOB_AJOB_H__

# include "../yuni.h"
# include "../thread/thread.h"
# include "../core/string.h"



namespace Yuni
{

/*!
** \brief Jobs (Multithreading programming)
** \ingroup Jobs
*/
namespace Job
{

	/*!
	** \brief Set of possible states for a single job
	**
	** \ingroup Jobs
	*/
	enum State
	{
		//! The job does nothing
		stateIdle = 0,
		//! The job is currently running
		stateRunning = 1,
		//! The job is running but has been suspended
		stateSleeping = 2,
	};



	enum Priority
	{
		//! Low priority
		priorityLow = 0,
		//! Default priority
		priorityDefault = 1,
		//! High priority
		priorityHigh = 2,

		priorityCount = 3,
	};






	/*!
	** \brief Job Interface (abstract)
	** \ingroup Jobs
	*/
	class IJob : public Policy::ObjectLevelLockable<IJob>
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<IJob>  Ptr;
		//! The threading policy
		typedef Policy::ObjectLevelLockable<IJob>  ThreadingPolicy;
		//! List of jobs
		typedef std::list<Ptr> List;

	public:
		//! \name Contructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		IJob();
		//! Destructor
		virtual ~IJob();
		//@}

		//! \name ID Card
		//@{
		//! Get the full human-readable name of this job
		String name() const;
		//! Set the name of the job
		template<class AnyStringT> void name(const AnyStringT& s);
		//@}

		//! \name Progression
		//@{
		/*!
		** \brief Get the progression in percent (value between 0.0 and 1.0)
		*/
		float progression() const;

		/*!
		** \brief Get if the job is finished
		**
		** This is a convenient (and faster) replacement for the following code :
		** \code
		** (state() == stateIdle && progression() >= 1.f)
		** \endcode
		*/
		bool finished() const;
		//@}


		//! \name States
		//@{
		//! Get the current state of the job
		int state() const;

		//! Get if the job is idle
		bool idle() const;
		//! Get if the job is running
		bool running() const;
		//! Get if the job is sleeping (the state can be in `running` in the same time)
		bool sleeping() const;
		//@}


		//! \name Execution flow
		//@{
		/*!
		** \brief Execute the job
		*/
		void execute();
		//@}


		//! \name Relation to a thread
		//@{
		/*!
		** \brief Attach this job to a given thread
		** \param t The thread which execute this job
		*/
		void attachToThread(Thread::AThread* t);

		/*!
		** \brief Get the attached thread
		** \return The attached thread. Null if no thread is attached
		*/
		Thread::AThread* attachedThread() const;

		/*!
		** \brief Detach this job from the previously attached thread
		*/
		void detachFromThread();
		//@}


	protected:
		/*!
		** \brief Implement this method to define the job
		** \return True to execute again this job
		*/
		virtual bool onExecute() = 0;

		/*!
		** \brief Set the progression in percent (0..1)
		*/
		void progression(const float);

		/*!
		** \brief Suspend the execution of the job during X miliseconds
		**
		** This method is nearly identical to AThread::suspend() in its behavior.
		** But this method should not have to be called in most of the jobs,
		** except when polling events or equivalent.
		** If you only want to know if the job should abort, prefer shouldAbort()
		** instead.
		**
		** \attention This method must only be called inside the execution of the job
		**
		** \param delay The delay in miliseconds. 0 will only return if the thread should exit
		** \return True indicates that the job should stop immediately
		** \see AThread::suspend()
		*/
		bool suspend(const unsigned int delay = 0);

		/*!
		** \brief Get if the job should abort as soon as possible
		**
		** This is a convenient routine instead of `suspend(0)`, but a bit faster.
		**
		** \attention This method must only be called inside the execution of the job
		** \return True indicates that the thread should stop immediately
		*/
		bool shouldAbort();


	private:
		//! State of the job
		Atomic::Int<32> pState;
		//! Name of the job
		String pName;
		//! Progression
		float pProgression;
		//! The attached thread to this job, if any
		Thread::AThread* pThread;

	}; // class IJob






} // namespace Job
} // namespace Yuni

# include "job.hxx"

#endif // __YUNI_JOB_AJOB_H__
