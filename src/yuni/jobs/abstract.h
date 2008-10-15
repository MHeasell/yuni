#ifndef __YUNI_JOBS_ABSTRACT_H__
# define __YUNI_JOBS_ABSTRACT_H__

# include "../yuni.h"
# include "../threads/thread.h"
# include "../string.h"



namespace Yuni
{
namespace Jobs
{

	/*!
	** \brief Priority for a single job
	*/
	enum Priority
	{
		//! Priority : The lowest
		prLowest = -2,
		//! Priority : Below than normal
		prBelowNormal = -1,
		//! Priority : Normal
		prNormal = 0,
		//! Priority : Above than normal
		prAboveNormal = 1,
		//! Priority : The highest
		prHighest = 2
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


		//! \name Priority
		//@{
		//! Get the priority of this job
		Priority priority();
		//! Set the priority of this job
		void priority(const Priority p);
		//@}

		//! \name Relation to a thread
		//@{

		/*!
		** \brief Attach this job to a given thread
		** \param t The thread which execute this job
		*/
		void attachToThread(Threads::Private::AbstractThreadModel* t);
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
		//! Name of the job
		String pName;
		//! Priority for this job
		Priority pPriority;
		//! The attached thread to this job, if any
		Threads::Private::AbstractThreadModel* pThread;

	}; // class Job




} // namespace Jobs
} // namespace Yuni

#endif // __YUNI_JOBS_ABSTRACT_H__
