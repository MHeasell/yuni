#ifndef __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__
# define  __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__

# include "../../yuni.h"
# include "../queue/waitingroom.h"
# include "../job.h"
# include "../queue/thread.h"
# include "../../thread/array.h"



namespace Yuni
{
namespace Job
{
namespace Scheduler
{


	/*!
	** \brief Basic Scheduler, where the job with the highest priority is executed in first
	*/
	class HighestPriorityFirst
	{
	public:
		typedef HighestPriorityFirst SchedulerType;

		enum
		{
			minimumThreadCount = 1,
			maximumThreadCount = (unsigned int) -1,
		};


	public:
		/*!
		** \brief Constructor
		**
		** \param room Reference to the Waiting room
		*/
		HighestPriorityFirst(Private::QueueService::WaitingRoom& room)
			:pWaitingRoom(room), pStarted(0)
		{
		}

		//! Destructor
		~HighestPriorityFirst()
		{
			if (pStarted)
			{
				pStarted = 0;
				pServiceMutex.lock();
				pThreads.stop();
				pServiceMutex.unlock();
			}
		}


		/*!
		** \brief Start all threads to execute the jobs
		*/
		bool start()
		{
			if (!pStarted)
			{
				pStarted = 1;
				pServiceMutex.lock();

				// Creating all threads we need
				pThreads.clear();
				for (int i = 0; i < 10; ++i)
					pThreads += new Yuni::Private::Jobs::QueueThread<SchedulerType>(*this);

				// Starting all threads at once
				pThreads.start();
				pServiceMutex.unlock();
			}
			return true;
		}


		/*!
		** \brief Stop all working threads
		*/
		bool stop(unsigned int timeout)
		{
			if (pStarted)
			{
				pStarted = 0;
				pServiceMutex.lock();
				// Stopping all threads
				pThreads.stop(timeout);
				pThreads.clear();
				pServiceMutex.unlock();
			}
			return true;
		}

		/*!
		** \brief Event: A job has just been added into the waiting room
		**
		** \param priority The priority of this job
		*/
		void newJobInWaitingRoom(Yuni::Job::Priority)
		{
			pThreads.wakeUp();
		}


		/*!
		** \brief Get the next job to execute
		*/
		bool nextJob(IJob::Ptr& out)
		{
			while (!pWaitingRoom.empty())
			{
				if (pWaitingRoom.hasJob[priorityHigh])
				{
					if (pWaitingRoom.pop(out, priorityHigh))
						return true;
					continue;
				}
				if (pWaitingRoom.hasJob[priorityDefault])
				{
					if (pWaitingRoom.pop(out, priorityDefault))
						return true;
					continue;
				}
				if (pWaitingRoom.hasJob[priorityLow])
				{
					if (pWaitingRoom.pop(out, priorityLow))
						return true;
					continue;
				}
			}
			return false;
		}


		/*!
		** \brief Get the number of threads currently in use
		*/
		unsigned int threadCount() const
		{
			return pThreads.count();
		}

		template<class PredicateT>
		void foreachThread(PredicateT& predicate)
		{
			pThreads.foreachThread(predicate);
		}

	public:
		//! Index of the next thread to wake up
		Atomic::Int<32> pRunningThreads;

		//! Reference to the array of threads
		Yuni::Thread::Array<Yuni::Private::Jobs::QueueThread<SchedulerType> >  pThreads;
		//! Reference to the waiting room
		Private::QueueService::WaitingRoom& pWaitingRoom;
		//! Mutex, used for start/stop methods
		Mutex pServiceMutex;
		//! Flag to know if the scheduler is started
		Atomic::Int<32> pStarted;

	}; // class HighestPriorityFirst





} // namespace Scheduler
} // namespace Job
} // namespace Yuni

# include "highestpriorityfirst.hxx"

#endif // __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__
