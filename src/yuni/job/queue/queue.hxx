#ifndef __YUNI_JOB_QUEUE_QUEUE_HXX__
# define __YUNI_JOB_QUEUE_QUEUE_HXX__

# include "../../thread/timer.h"


namespace Yuni
{
namespace Job
{



	template<class SchedulerT>
	inline QueueService<SchedulerT>::QueueService()
		:pWaitingRoom(), pScheduler(pWaitingRoom)
	{}

	template<class SchedulerT>
	QueueService<SchedulerT>::QueueService(bool autostart)
		:pWaitingRoom(), pScheduler(pWaitingRoom)
	{
		if (autostart)
			start();
	}




	template<class SchedulerT>
	QueueService<SchedulerT>::~QueueService()
	{
		if (pStarted)
		{
			// For the execution of all jobs
			wait();
			// Stop the service wahtever the result of the previous method
			stop();
		}
	}


	template<class SchedulerT>
	bool QueueService<SchedulerT>::start()
	{
		if (!pStarted)
		{
			pStarted = 1;
			pScheduler.start();
		}
		return true;
	}


	template<class SchedulerT>
	bool QueueService<SchedulerT>::stop(unsigned int timeout)
	{
		if (pStarted)
		{
			pStarted = 0;
			pScheduler.stop(timeout);
		}
		return true;
	}


	template<class SchedulerT>
	inline bool QueueService<SchedulerT>::restart(unsigned int timeout)
	{
		return (pScheduler.stop(timeout) && pScheduler.start());
	}



	class QueueServicePoll : public Thread::Timer
	{
	public:
		QueueServicePoll(Yuni::Private::QueueService::WaitingRoom& room, unsigned int pollInterval)
			:Thread::Timer(pollInterval), pRoom(room), pStatus(false)
		{}
		virtual ~QueueServicePoll()
		{
			stop();
		}

		bool status() const {return pStatus;}

	protected:
		virtual bool onInterval(unsigned int)
		{
			if (pRoom.empty())
			{
				pStatus = true;
				// We can stop now
				return false;
			}
			// Continuing...
			return true;
		}

	private:
		Yuni::Private::QueueService::WaitingRoom& pRoom;
		bool pStatus;
	};



	template<class SchedulerT>
	bool QueueService<SchedulerT>::wait(unsigned int timeout, unsigned int pollInterval)
	{
		if (pWaitingRoom.notEmpty())
		{
			QueueServicePoll wait(pWaitingRoom, pollInterval);
			wait.start();
			wait.wait(timeout);
			return wait.status();
		}
		return true;
	}




	template<class SchedulerT>
	void QueueService<SchedulerT>::add(IJob* job)
	{
		if (job)
		{
			pWaitingRoom.add(job);
			pScheduler.newJobInWaitingRoom(priorityDefault);
		}
	}


	template<class SchedulerT>
	void QueueService<SchedulerT>::add(const IJob::Ptr& job)
	{
		if (!(!job))
		{
			pWaitingRoom.add(job);
			pScheduler.newJobInWaitingRoom(priorityDefault);
		}
	}


	template<class SchedulerT>
	void QueueService<SchedulerT>::add(const IJob::Ptr& job, Priority priority)
	{
		if (!(!job))
		{
			pWaitingRoom.add(job, priority);
			pScheduler.newJobInWaitingRoom(priority);
		}
	}


	template<class SchedulerT>
	void QueueService<SchedulerT>::add(IJob* job, Priority priority)
	{
		if (job)
		{
			pWaitingRoom.add(job, priority);
			pScheduler.newJobInWaitingRoom(priority);
		}
	}


	template<class SchedulerT>
	inline unsigned int QueueService<SchedulerT>::size() const
	{
		return pWaitingRoom.size();
	}


	template<class SchedulerT>
	inline unsigned int QueueService<SchedulerT>::count() const
	{
		return pWaitingRoom.size();
	}


	template<class SchedulerT>
	inline QueueService<SchedulerT>& QueueService<SchedulerT>::operator += (IJob* job)
	{
		add(job);
		return *this;
	}


	template<class SchedulerT>
	inline QueueService<SchedulerT>& QueueService<SchedulerT>::operator << (IJob* job)
	{
		add(job);
		return *this;
	}


	template<class SchedulerT>
	inline QueueService<SchedulerT>& QueueService<SchedulerT>::operator += (const IJob::Ptr& job)
	{
		add(job);
		return *this;
	}


	template<class SchedulerT>
	inline QueueService<SchedulerT>& QueueService<SchedulerT>::operator << (const IJob::Ptr& job)
	{
		add(job);
		return *this;
	}


	template<class SchedulerT>
	inline unsigned int QueueService<SchedulerT>::threadCount() const
	{
		return pScheduler.threadCount();
	}


	template<class SchedulerT>
	class ActivityPredicate
	{
	public:
		//!
		typedef typename QueueService<SchedulerT>::ThreadInfo ThreadInfoType;
		typedef typename ThreadInfoType::Vector VectorType;

	public:
		ActivityPredicate(VectorType& out)
			:pList(out)
		{
			pList.clear();
		}

		template<class ThreadPtrT>
		bool operator () (const ThreadPtrT& thread)
		{
			ThreadInfoType* info = new ThreadInfoType();
			info->thread = thread;
			if (!(!(info->thread)))
			{
				info->job = thread->currentJob();
				if (!(!(info->job)))
				{
					// We have a job which is currently working !
					info->hasJob = true;
					info->job->fillInformation(*info);
					pList.push_back(info);
					return true;
				}
			}
			info->hasJob = false;
			info->state = Yuni::Job::stateIdle;
			info->canceling = false;
			info->progression = 0;
			pList.push_back(info);
			return true;
		}

	private:
		VectorType& pList;
	};


	template<class SchedulerT>
	inline void QueueService<SchedulerT>::activitySnapshot(
		typename QueueService<SchedulerT>::ThreadInfo::Vector& out)
	{
		ActivityPredicate<SchedulerT> predicate(out);
		pScheduler.foreachThread(predicate);
	}





} // namespace Job
} // namespace Yuni

#endif // __YUNI_JOB_QUEUE_QUEUE_H__
