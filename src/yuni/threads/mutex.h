#ifndef __YUNI_THREADS_MUTEX_H__
# define __YUNI_THREADS_MUTEX_H__

# include <pthread.h>



namespace Yuni
{


    /*! \class Mutex
    **
    ** \brief  Mechanism to avoid the simultaneous use of a common resource
    */
    class Mutex 
    {
    public:
        //! \name Constructor & Destructor
        //@{
        //! Default constructor
        Mutex();
        //! Destructor
        ~Mutex() {pthread_mutex_destroy(&pPthreadLock);}
        //@}

        /*!
        ** \brief Lock the mutex
        */
        void lock() {pthread_mutex_lock(&pPthreadLock);}

        /*!
        ** \brief Release the lock
        */
        void unlock() {pthread_mutex_unlock(&pPthreadLock);}
    
        /*!
        ** \brief Get the original PThread mutex
        */
        pthread_mutex_t& pthreadMutex() {return pPthreadLock;}

    private:
        //! The PThread mutex
        pthread_mutex_t pPthreadLock;

    }; // class Mutex



    /*! \class MutexLocker
    **
    ** \code
    **      class Foo
    **      {
    **      public:
    **          Foo() : pValue(42) {}
    **          ~Foo() {}
    **          int getValue()
    **          {
    **              MutexLocker locker(pMutex);
    **              return pValue;
    **          }
    **          void setValue(const int i)
    **          {
    **              pMutex.lock();
    **              pValue = i;
    **              pMutex.unlock();
    **          }
    **      private:
    **          int pValue;
    **          Mutex pMutex;
    **      };
    ** \endcode
    */
    class MutexLocker
    {
    public:
        MutexLocker(Mutex& m) : pMutex(m) { m.lock(); }
        ~MutexLocker() { pMutex.unlock(); }
    private:
        Mutex& pMutex;

    }; // MutexLocker


} // namespace Yuni

#endif // __YUNI_THREADS_MUTEX_H__
