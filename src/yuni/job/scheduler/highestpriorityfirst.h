#ifndef __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__
# define  __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__


namespace Yuni
{
namespace Job
{
namespace Scheduler
{


	class HighestPriorityFirst
	{
	public:
		enum
		{
			minimumThreadCount = 1,
			maximumThreadCount = (unsigned int) -1,
		};

		/*!
		** \brief Additional data to attach to each thread
		*/
		class ThreadInfo
		{
		public:
			ThreadInfo() {}
			~ThreadInfo() {}
		};

	public:
		HighestPriorityFirst() {}

		void add(const IJob::Ptr& job, Priority priority)
		{
			pWaitingRoom.add(job, priority);
		}

		void resizeThreadPool(unsigned int min, unsigned int max)
		{

		}

		bool nextJob(WaitingRoom& room, IJob::Ptr& out, ThreadInfo& info)
		{
			while (1)
			{
				if (room.hasJob[priorityHigh])
				{
					if (room.pop(out, priorityHigh))
						return;
					continue;
				}
				if (room.hasJob[priorityDefault])
				{
					if (room.pop(out, priorityDefault))
						return;
					continue;
				}
				if (room.hasJob[priorityLow])
				{
					if (room.pop(out, priorityLow))
						return;
					continue;
				}
			}
		}

	public:
		std::vector<AThread*> pool;
		Private::Queue::WaitingRoom pWaitingRoom;

	};





} // namespace Scheduler
} // namespace Job
} // namespace Yuni

#endif // __YUNI_JOB_SCHEDULER_HIGHEST_PRIORITY_FIRST_H__
