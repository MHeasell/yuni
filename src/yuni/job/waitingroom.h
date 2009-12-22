#ifndef __YUNI_JOB_WAITING_ROOM_H__
# define __YUNI_JOB_WAITING_ROOM_H__

# include "job.h"


namespace Yuni
{
namespace Private
{
namespace Queue
{


	class WaitingRoom
	{
	public:
		enum
		{
			priorityCount = Yuni::Job::priorityCount,
		};

	public:
		WaitingRoom() {}
		~WaitingRoom() {}

		/*!
		** \brief Add a job
		**
		** \param job The job to add
		** \param priority Its priority
		*/
		void add(const Yuni::Job::IJob::Ptr& job, Yuni::Job::Priority priority);

		/*!
		** \brief Get the next job to execute for a given priority
		**
		** \param[out] out Job to execute, if any. It will remain untouched if
		**   no job can be found.
		** \param priority The priority queue where to look for
		** \return True if a job is actually available
		*/
		bool pop(Yuni::Job::IJob::Ptr& out, const Yuni::Job::Priority priority);

	public:
		//! Flags to indicate if there are some remaining jobs by priority
		Atomic::Int<32> hasJob[priorityCount];

	private:
		//! List of waiting jobs by priority
		std::list<Yuni::Job::IJob::Ptr> pJobs[priorityCount];
		//! Mutex by priority to reduce congestion
		Mutex pMutexes[priorityCount];

	}; // class WaitingRoom



} // namespace Queue
} // namespace Private
} // namespace Yuni

#endif // __YUNI_JOB_WAITING_ROOM_H__
