
#include "waitingroom.h"


namespace Yuni
{
namespace Private
{
namespace Queue
{


	void WaitingRoom::add(const Yuni::Job::IJob::Ptr& job, Yuni::Job::Priority priority)
	{
		MutexLocker locker(pMutexes[priority]);
		pJobs[priority].push_back(job);
		hasJob[priority] = 1;
	}


	bool WaitingRoom::pop(Yuni::Job::IJob::Ptr& out, const Yuni::Job::Priority priority)
	{
		MutexLocker locker(pMutexes[priority]);
		if (!pJobs[priority].empty())
		{
			hasJob[priority] = pJobs[priority].empty() ? 0 : 1;
			out = pJobs[priority].front();
			pJobs[priority].pop_front();
			return true;
		}
		hasJob[priority] = 0;
		return false;
	}




} // namespace Queue
} // namespace Private
} // namespace Yuni


