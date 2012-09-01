#ifndef __YUNI_THREADS_SEMAPHORE_HXX__
# define __YUNI_THREADS_SEMAPHORE_HXX__


namespace Yuni
{

	inline Semaphore::Semaphore(uint readers)
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		sem_init(& pSemaphore, 0, readers);
		# endif
		# endif
	}


	inline Semaphore::~Semaphore()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		sem_destroy(& pSemaphore);
		# endif
		# endif
	}


	inline void Semaphore::acquire()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		sem_wait(& pSemaphore);
		# endif
		# endif
	}


	inline void Semaphore::acquire(uint n)
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		for (uint i = 0; i != n; ++i)
			sem_wait(& pSemaphore);
		# endif
		# endif
	}


	inline void Semaphore::release()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		sem_post(& pSemaphore);
		# endif
		# endif
	}


	inline void Semaphore::release(uint n)
	{
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		for (uint i = 0; i != n; ++i)
			sem_post(& pSemaphore);
		# endif
		# endif
	}


	inline Semaphore& Semaphore::operator -- ()
	{
		acquire();
		return *this;
	}


	inline Semaphore& Semaphore::operator ++ ()
	{
		release();
		return *this;
	}


	inline Semaphore& Semaphore::operator = (const Semaphore&)
	{
		// Do nothing on purpose
		return *this;
	}




} // namespace Yuni

#endif // __YUNI_THREADS_SEMAPHORE_HXX__

