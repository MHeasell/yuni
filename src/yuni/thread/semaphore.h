#ifndef __YUNI_THREADS_SEMAPHORE_H__
# define __YUNI_THREADS_SEMAPHORE_H__

# include "../yuni.h"
# ifndef YUNI_NO_THREAD_SAFE
#	include "../include/semaphore.h" // unix
#	ifdef YUNI_OS_WINDOWS
#		include "../core/system/windows.hdr.h"
# 	endif
# endif




namespace Yuni
{

	/*!
	**
	*/
	class YUNI_DECL Semaphore
	{
	public:
		/*!
		** \brief Default constructor
		*/
		Semaphore(uint readers = 64);
		//! Destructor
		~Semaphore();
		//@}


		//! \name Acquire / release
		//@{
		/*!
		** \brief Acquire 1 resource
		**
		** If there aren't that many resources available, the call will block until this is the case.
		*/
		void acquire();
		/*!
		** \brief Acquire n resources
		**
		** If there aren't that many resources available, the call will block until this is the case.
		*/
		void acquire(uint n);

		/*!
		** \brief Release 1 resource
		*/
		void release();
		/*!
		** \brief Release n resources
		*/
		void release(uint n);
		//@}


		//! \name Operators
		//@{
		//! Try to acquire a resource
		Semaphore& operator -- ();
		//! Release a resource
		Semaphore& operator ++ ();
		//! Copy operator
		Semaphore& operator = (const Semaphore&);
		//@}


	private:
		# ifndef YUNI_NO_THREAD_SAFE
		# ifdef YUNI_OS_WINDOWS
		# else
		//! Pthread semaphore
		::sem_t pSemaphore;
		# endif
		# endif

	}; // class Semaphore





} // namespace Yuni

# include "semaphore.hxx"

#endif // __YUNI_THREADS_SEMAPHORE_H__
