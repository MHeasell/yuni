#ifndef __YUNI_THREADS_CONDITION_H__
# define __YUNI_THREADS_CONDITION_H__

# include "mutex.h"
# include "../core/smartptr/smartptr.h"


namespace Yuni
{
namespace Threads
{


	/*!
	** \brief Condition Variable
	** \ingroup Threads
	**
	** A condition variable is a synchronization object used in conjunction with a
	** mutex. It is a synchronization mechanism that allows a thread to suspend its
	** execution until some predicate is verified.
	**
	** \see samples/threads/01.condition/main.cpp
	*/
	class Condition
	{
	public:
		//! The most suitable SmartPtr
		typedef SmartPtr<Condition> Ptr;

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Condition();
		/*!
		** \brief Constructor with an external mutex
		**
		** In this case, an external mutex will be used
		*/
		Condition(Mutex& mutex);
		//! Destructor
		~Condition();
		//@}

		//! \name Wait for the condition
		//@{
		/*!
		** \brief Wait the condition
		**
		** This method blocks the calling thread until the condition
		** is met.
		** The mutex will remain locked at the end of this method. It is
		** the responsability of the user to unlock the mutex.
		** This metod is a cancellation point.
		**
		** \see unlock()
		*/
		void wait();

		/*!
		** \brief Wait the condition (with a timeout)
		**
		** This method blocks the calling thread until the condition
		** is met.
		** The mutex will remain locked at the end of this method. It is
		** the responsability of the user to unlock the mutex.
		** This metod is a cancellation point.
		**
		** \param timeout The timeout value (in seconds)
		** return True if the timeout has been reached 
		** \see unlock()
		*/
		bool wait(unsigned int timeout);

		/*!
		** \brief Unlock the inner mutex
		*/
		void unlock();
		//@}

		//! \name Notify that the condition has been met
		//@{
		/*!
		** \brief Notify at least one thread that the condition has been met
		**
		** If more than one thread is waiting for a condition variable, the scheduling
		** policy determines the order in which threads are notified.
		** If no threads are currently waiting for the condition, this call has no effect.
		*/
		void notify();


		/*!
		** \brief Notify all threads that the condition has been met
		**
		** If no threads are currently waiting for the condition, this call has no effect.
		*/
		void notifyAllThreads();
		//@}

		/*!
		** \bief Get the inner mutex
		*/
		Mutex& mutex() const;

	private:
		//! The PThread Condition
		pthread_cond_t  pCondition;
		//! The mutex
		Mutex* pMutex;
		//! Out predicate (bool)
		bool pPredicate;
		//! True if this class owns the mutex and must destroy it
		const bool pOwnMutex;

	}; // class Condition


} // namespace Threads
} // namespace Yuni

# include "condition.hxx"

#endif // __YUNI_THREADS_CONDITION_H__
