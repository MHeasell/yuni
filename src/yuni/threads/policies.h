#ifndef __YUNI_THREADS_POLICIES_H__
# define __YUNI_THREADS_POLICIES_H__

# ifdef YUNI_WINDOWS
#	include "../system/windows.hdr.h"
# endif
# include "mutex.h"



namespace Yuni
{
namespace Threads
{
namespace Policy
{


	/*!
	** \brief Implementation of the Threading Model policy in a single-threaded environnement
	**
	** No synchronization is required in this case
	*/
	template<class Host>
	class SingleThreaded
	{
	public:
		/*!
		** \brief Locks a mutex in the constructor and unlocks it in the destructor.
		*/
		class MutexLocker
		{
		public:
			MutexLocker(Host&) {}
			~MutexLocker() {}
		}; // class MutexLocker

	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		SingleThreaded() {}
		//! Copy constructor
		SingleThreaded(const SingleThreaded&) {}
		//! Destructor
		~SingleThreaded() {}
		//@}

	}; // class SingleThreaded



	/*!
	** \brief Implementation of the Threading Model policy in a multi-threaded environnement (one mutex per object)
	*/
	template<class Host>
	class ObjectLevelLockable
	{
	public:
		/*!
		** \brief Locks a mutex in the constructor and unlocks it in the destructor.
		*/
		class MutexLocker
		{
		public:
			template<class C> MutexLocker(C& h) :pHostToLock(static_cast<Host&>(h)) {pHostToLock.pMutex.lock();}
			~MutexLocker() {pHostToLock.pMutex.unlock();}
		private:
			Host& pHostToLock;
		}; // class MutexLocker
		
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		ObjectLevelLockable() :pMutex(true) {}
		//! Copy constructor
		ObjectLevelLockable(const ObjectLevelLockable&) :pMutex(true) {}
		//! Destructor
		~ObjectLevelLockable() {}
		//@}

	protected:
		//! Mutex
		mutable Mutex pMutex;

	}; // class ObjectLevelLockable




	/*!
	** \brief Implementation of the Threading Model policy in a multi-threaded environnement (one mutex per class)
	*/
	template<class Host>
	class ClassLevelLockable
	{
	public:
		/*!
		** \brief Locks a mutex in the constructor and unlocks it in the destructor.
		*/
		class MutexLocker
		{
		public:
			template<class C> MutexLocker(C&) {Mutex::ClassLevelLockable<Host>::mutex.lock();}
			~MutexLocker() {Mutex::ClassLevelLockable<Host>::mutex.unlock();}
		}; // class MutexLocker
		
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		ClassLevelLockable() :pMutex(Mutex::ClassLevelLockable<Host>::mutex) {}
		//! Copy constructor
		ClassLevelLockable(const ClassLevelLockable&) :pMutex(Mutex::ClassLevelLockable<Host>::mutex) {}
		//! Destructor
		~ClassLevelLockable() {}
		//@}

	protected:
		//! Mutex
		mutable Mutex& pMutex;

	}; // class ClassLevelLockable




} // namespace Models
} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_POLICIES_H__
