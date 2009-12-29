#ifndef __YUNI_JOB_QUEUE_THREAD_H__
# define __YUNI_JOB_QUEUE_THREAD_H__

# include "../../thread/thread.h"
# include "../job.h"


namespace Yuni
{
namespace Private
{
namespace Jobs
{


	template<class SchedulerT>
	class QueueThread : public Yuni::Thread::IThread
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<QueueThread<SchedulerT> > Ptr;
		//! Scheduler Policy
		typedef SchedulerT SchedulerType;

	public:
		QueueThread(SchedulerType& scheduler)
			:pScheduler(scheduler)
		{}

		virtual ~QueueThread()
		{
			// Ensure that the thread is really stopped
			stop();
		}


		Yuni::Job::IJob::Ptr currentJob() const
		{
			return pJob;
		}


	protected:
		virtual bool onExecute()
		{
			// assert
			assert(this != NULL && "Queue: Thread: Oo `this' is null !?");

			// Asking for the next job
			while (pScheduler.nextJob(pJob))
			{
				// Cancellation point
				// It is actually better to perform the test before executing the job
				if (shouldAbort())
				{
					// We have to stop, no need for hibernating
					return false;
				}

				// Execute the job, via a wrapper for visibility issues
				Yuni::Private::QueueService::JobAccessor<Yuni::Job::IJob>::Execute(*pJob, this);

				// We must release our pointer to the job here to avoid its destruction
				// in `pScheduler.nextJob()` (when `pJob` is re-assigned).
				// This method uses a lock and the destruction of the job may take some
				// time.
				// However, there is absolutely no guarantee that the job will be
				// destroyed in this thread.
				pJob = nullptr;
			}

			// Returning true, for hibernation
			return true;
		}


		virtual void onKill()
		{
			if (!(!(pJob)))
			{
				Yuni::Private::QueueService::JobAccessor<Yuni::Job::IJob>::ThreadHasBeenKilled(*pJob);
				pJob = nullptr;
			}
		}

	private:
		//! The current job
		Yuni::Job::IJob::Ptr pJob;
		//! The scheduler
		SchedulerType& pScheduler;

	}; // class QueueThread





} // namespace Jobs
} // namespace Private
} // namespace Yuni


#endif // __YUNI_JOB_QUEUE_THREAD_H__
