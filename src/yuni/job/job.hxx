#ifndef __YUNI_JOB_AJOB_HXX__
# define __YUNI_JOB_AJOB_HXX__


namespace Yuni
{
namespace Job
{

	inline IJob::IJob()
		:pProgression(0.0f), pThread(NULL)
	{}


	inline IJob::~IJob()
	{}



	inline int IJob::state() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pState;
	}


	inline bool IJob::idle() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pState & stateIdle;
	}

	inline bool IJob::running() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pState & stateRunning;
	}

	inline bool IJob::sleeping() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pState & stateSleeping;
	}


	inline void IJob::attachToThread(Thread::AThread* t)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pThread = t;
	}


	inline void IJob::detachFromThread()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pThread = NULL;
	}


	inline Thread::AThread* IJob::attachedThread() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pThread;
	}


	inline String IJob::name() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pName;
	}

	template<class AnyStringT> inline void IJob::name(const AnyStringT& s)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = s;
	}


	inline void IJob::progression(const float p)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pProgression = p;
	}


	inline bool IJob::finished() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return (pState == stateIdle && pProgression >= 1.f);
	}






} // namespace Job
} // namespace Yuni

#endif // __YUNI_JOB_AJOB_HXX__
