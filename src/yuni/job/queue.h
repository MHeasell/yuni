#ifndef __YUNI_JOB_QUEUE_H__
# define __YUNI_JOB_QUEUE_H__

# include "../yuni.h"
# include "job.h"
# include <list>
# include "scheduler/highestpriorityfirst.h"


namespace Yuni
{
namespace Job
{



	/*!
	** \brief A Multithreaded Job Queue
	**
	** \todo Use a better scheduling algorithm for distributing jobs
	*/
	template<class SchedulerT = Scheduler::HighestPriorityFirst>
	class Queue : public Policy::ObjectLevelLockable<Queue>
	{
	public:
		//! The threading policy
		typedef Policy::ObjectLevelLockable<Queue> ThreadingPolicy;
		//! The most suitable smart pointer for the class
		typedef SmartPtr<Queue> Ptr;

		//! The Scheduler policy
		typedef SchedulerT  SchedulerPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		Queue();
		~Queue();
		//@}


		//! \name Service
		//@{
		/*!
		** \brief Start the service and execute the jobs
		*/
		bool start();

		/*!
		** \brief Stop the service
		**
		** All unfinished jobs will be kept and re-executed at the next start.
		** It is of their responsibility to properly resume if they have to.
		** All working threads will be destroyed at the very end of this method.
		*/
		bool stop(unsigned int timeout = AThread::defaultTimeout);

		/*!
		** \brief Stop then start the service
		**
		** All unfinished jobs will be kept and re-executed at the next start.
		** It is of their responsibility to properly resume if they have to.
		*/
		bool restart(unsigned int timeout = ATHread::defaultTimeout);

		/*!
		** \brief Get if the service is started
		*/
		bool started() const;
		//@}


		//! \name Job handling
		//@{
		void add(const IJob::Ptr& job)
		{
			pScheduler.add(job, priorityDefault);
		}

		void add(const IJob::Ptr& job, Priority priority)
		{
			pScheduler.add(job, priority);
		}

		/*!
		** \brief Retrieve the list of all currently running jobs
		**
		** \note Event if in the list, a job may already have finished
		**   at the end of this method.
		*/
		void listOfRunningJobs(IJob::List& out);
		//@}



		//! \name Threads
		//@{
		unsigned int threadCount() const;

		unsigned int minimumThreadCount() const;
		bool minimumThreadCount(unsigned int n);

		unsigned int maximumThreadCount() const;
		bool maximumThreadCount(unsigned int n);
		//@}

		//! \name Operators
		//@{
		Queue& operator += (const IJob::Ptr& job) {pScheduler.add(job, priorityDefault);}
		Queue& operator << (const IJob::Ptr& job) {pScheduler.add(job, priorityDefault);}
		//@}


	private:
		SchedulerPolicy pScheduler;

	}; // class Queue





} // namespace Job
} // namespace Yuni


#endif // __YUNI_JOB_QUEUE_H__
