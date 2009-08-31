#ifndef __YUNI_THREADS_CONDITION_HXX__
# define __YUNI_THREADS_CONDITION_HXX__



namespace Yuni
{
namespace Threads
{

	// Condition
	inline Mutex& Condition::mutex() const
	{
		return *pMutex;
	}

	inline void Condition::lock()
	{
		pMutex->lock();
	}

	inline void Condition::unlock()
	{
		pMutex->unlock();
	}

	inline void Condition::notify()
	{
		pSignalled = true;
		::pthread_cond_signal(&pCondition);
	}

	inline void Condition::notifyAll()
	{
		pSignalled = true;
		::pthread_cond_broadcast(&pCondition);
	}

	// ConditionLocker
	inline ConditionLocker::ConditionLocker(Condition& c)
		:pCondition(c)
	{
		c.lock();
	}

	inline ConditionLocker::~ConditionLocker()
	{
		pCondition.unlock();
	}

} // namespace Threads
} // namespace Yuni


#endif // __YUNI_THREADS_CONDITION_HXX__
