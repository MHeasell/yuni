#ifndef __YUNI_THREADS_MUTEX_H__
# define __YUNI_THREADS_MUTEX_H__

# include <pthread.h>
# include "../yuni.h"



namespace Yuni
{


	/*!
	** \brief  Mechanism to avoid the simultaneous use of a common resource
	** \ingroup Threads
	*/
	class Mutex
	{
	public:
		/*!
		** \brief A class-level locking mechanism
		**
		** A class-level locking operation locks all objects in a given class during that operation
		*/
		template<class T>
		class ClassLevelLockable
		{
		public:
			//! A dedicated mutex for the class T
			static Mutex mutex;

		}; // class ClassLevelLockable


	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Mutex(const bool recursive = true);
		//! Destructor
		~Mutex() {pthread_mutex_destroy(&pPthreadLock);}
		//@}

		//! \name Lock & Unlock
		//@{

		/*!
		** \brief Lock the mutex
		*/
		void lock() {pthread_mutex_lock(&pPthreadLock);}

		/*!
		** \brief Release the lock
		*/
		void unlock() {pthread_mutex_unlock(&pPthreadLock);}

		//@}

		//! \name PThread wrapper
		//@{
		/*!
		** \brief Get the original PThread mutex
		*/
		pthread_mutex_t& pthreadMutex() {return pPthreadLock;}
		//@}

	private:
		//! The PThread mutex
		pthread_mutex_t pPthreadLock;

	}; // class Mutex





	/*! \class MutexLocker
	** \brief Locks a mutex in the constructor and unlocks it in the destructor.
	**
	** This class is especially usefull for `get` accessor` and/or returned values
	** which have to be thread-safe.
	**
	** \code
	**	  class Foo
	**	  {
	**	  public:
	**		  Foo() : pValue(42) {}
	**		  ~Foo() {}
	**		  int getValue()
	**		  {
	**			  MutexLocker locker(pMutex);
	**			  return pValue;
	**		  }
	**		  void setValue(const int i)
	**		  {
	**			  pMutex.lock();
	**			  pValue = i;
	**			  pMutex.unlock();
	**		  }
	**	  private:
	**		  int pValue;
	**		  Mutex pMutex;
	**	  };
	** \endcode
	*/
	class MutexLocker
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		**
		** \param m The mutex to lock
		*/
		MutexLocker(Mutex& m) : pMutex(m) { m.lock(); }
		//! Destructor
		~MutexLocker() { pMutex.unlock(); }
		//@}

		/*!
		** \brief Get the original mutex
		*/
		Mutex& mutex() const {return pMutex;}

	private:
		//! Reference to the real mutex
		Mutex& pMutex;

	}; // MutexLocker




	//! All mutexes for each class
	template<class T> Mutex Mutex::ClassLevelLockable<T>::mutex;





} // namespace Yuni

#endif // __YUNI_THREADS_MUTEX_H__
