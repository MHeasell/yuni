#ifndef __YUNI_THREADS_CONDITION_HXX__
# define __YUNI_THREADS_CONDITION_HXX__



namespace Yuni
{
namespace Threads
{


	inline Mutex& Condition::mutex() const
	{
		return *pMutex;
	}



} // namespace Threads
} // namespace Yuni


#endif // __YUNI_THREADS_CONDITION_HXX__
