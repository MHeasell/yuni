#ifndef __YUNI_JOBS_ABSTRACT_H__
# define __YUNI_JOBS_ABSTRACT_H__

# include "../yuni.h"
# include "../threads/thread.h"
# include "../toolbox/string.h"



namespace Yuni
{
namespace Jobs
{

	/*!
	** \brief Various states for a single job
	*/
	enum State
	{
		//! The job does nothing
		jsIdle = 0,
		//! The job is currently running
		jsRunning,
		//! The job is running but has been suspended
		jsSleeping
	};





	/*!
	** \brief Job Interface (abstract)
	** \ingroup Jobs
	*/
	class Abstract 
	{
	public:
		//! \name Contructor & Destructor
		//@{
		//! Default constructor
		Abstract();
		//! Destructor
		virtual ~Abstract();
		//@}

		//! \name Name of the job
		//@{
		//! Get the full human-readable name of this job
		String name();
		//! Set the name of the job
		void name(const String& n);
		//@}

		//! \name Progression
		//@{
		//! Get the progression in percent (value between 0.0 and 1.0)
		float progression();
		//@}

		//! \name State of the job
		//@{
		//! Get the current state of the job
		State state();
		//@}

		/*!
		** \brief Execute the job
		*/
		void execute();

		//! \name Relation to a thread
		//@{

		/*!
		** \brief Attach this job to a given thread
		** \param t The thread which execute this job
		*/
		void attachToThread(Threads::Private::AbstractThreadModel* t);

		/*!
		** \brief Get the attached thread
		** \return The attached thread. Null if no thread is attached
		*/
		Threads::Private::AbstractThreadModel* attachedThread();

		/*!
		** \brief Detach this job from the previous attached thread
		*/
		void detachFromThread() {attachToThread(NULL);}

		//@}


	protected:
		/*!
		** \brief Implement this method to define the job
		** \return True to execute again this job
		*/
		virtual bool onExecute() = 0;

		//! Set the progression in percent
		void progression(const float);

		/*!
		** \brief Suspend the execution of the job of X miliseconds
		**
		** This is a convenient method to know if the job should stop as soon as possible
		**
		** \param delay The delay in miliseconds. O will only return if the thred should exit
		** \return True indicates that the job should stop immediately
		**
		** \see AbstractThreadModel::suspend()
		*/
		bool suspend(const uint32 delay = 0);


	protected:
		//! Mutex for this job
		Mutex pMutex;

	private:
		//! State of the job
		State pState;
		//! Name of the job
		String pName;
		//! Progression
		float pProgression;
		//! The attached thread to this job, if any
		Threads::Private::AbstractThreadModel* pThread;

	}; // class Job




} // namespace Jobs
} // namespace Yuni

#endif // __YUNI_JOBS_ABSTRACT_H__
