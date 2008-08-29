#ifndef __YUNI_THREADS_JOBS_ABSTRACT_H__
# define __YUNI_THREADS_JOBS_ABSTRACT_H__

# include "yuni/yuni.h"
# include "yuni/string.h"
# include "yuni/threads/thread.h"
# include "yuni/string.h"



namespace Yuni
{
namespace Jobs
{


	/*!
	** \brief Job Interface
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

		/*!
		** \brief Implement this method to define the job
		** \return True to execute again this job
		*/
		virtual bool onExecute() = 0;

		//! Get the full human-readable name of this job
		String name();
		//! Set the name of the job
		void name(const String& n);

		//! Get the priority of this job
		sint8 priority();
		//! Set the priority of this job
		void priority(const int p);

		/*!
		** \brief Attach this job to a given thread
		** \param t The thread which execute this job
		*/
		void attachToThread(Threads::Private::AbstractThreadModel* t);
		/*!
		** \brief Detach this job from the previous attached thread
		*/
		void detachFromThread() {attachToThread(NULL);}


	protected:
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
		bool suspend(uint32 delay = 0);


	protected:
		//! Mutex for this job
		Mutex pMutex;

	private:
		//! Name of the job
		String pName;
		//! Priority for this job
		sint8 pPriority;
		//! The attached thread to this job, if any
		Threads::Private::AbstractThreadModel* pThread;

	}; // class Job


} // namespace Jobs
} // namespace Yuni

#endif // __YUNI_THREADS_JOBS_ABSTRACT_H__
