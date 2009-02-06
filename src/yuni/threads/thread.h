#ifndef __YUNI_THREADS_ATHREAD_H__
# define __YUNI_THREADS_ATHREAD_H__

# include "../yuni.h"
# include "mutex.h"
# include "abstract.thread.h"



namespace Yuni
{

/*!
** \brief Higher-level threading tools
*/
namespace Threads
{


	/*! \class AThread
	**  \brief Higher-level threading interface (abstract)
	**  \ingroup Threads
	**
	** To create your own thread, you only have to implement the methode execute(), as follow:
	** 
	** \code
	** class MyOwnThread : public Yuni::Threads::AThread
	** {
	** public:
	**   MyOwnThread(int p): Yuni::Threads::AThread(), pTag(p)  {}
	**   virtual ~MyOwnThread() {stop();} // Required
	**
	** protected:
	**   virtual void onExecute()
	**   {
	**      for (int i = 0; i < 50; ++i)
	**         std::cout << "Thread " << pTag << ": Do some stuff here" << std::endl;
	**   }
	**
	** private:
	**   int pTag;
	** };
	**
	**
	** int main(void)
	** {
	**     MyOwnThread t1(1);
	**     MyOwnThread t2(2);
	**     t1.start();
	**     t2.start();
	**     t1.stop();
	**     t2.stop();
	**     return 0;
	** }
	** \endcode
	*/
	class AThread : public Private::AThreadModel
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		AThread();
		//! Destructor
		virtual ~AThread();
		//@}

	protected:
		/*!
		** \brief Event: The thread has just been started
		**
		** This event is executed in the thread which has just been created.
		**
		** It can be directly stopped if returning false. However the `onStopped` event
		** will not be called.
		**
		** \return True to continue the execution of the thread, false to abort the
		** execution right now
		*/
		virtual bool onStarting() {return true;}

		/*!
		** \brief Event: The thread is running 
		**
		** The thread has been successfully started (that means `onStarting()` returned true)
		** As soon as this method exits, the other event `onStopped()` will be called.
		**
		** \attention This method should check from time to time if the thread have to stop. For that,
		** a call to `suspend(0)` is recommended.
		** \code
		**    if (suspend())
		**       return;
		** \endcode
		**
		** \see suspend()
		** \see onStarting()
		** \see onStopped()
		*/
		virtual void onExecute() = 0;

		/*!
		** \brief Event: The thread has been gracefully stopped
		**
		** This event is executed in the thread.
		**
		** \attention You should not rely on this event to release your resources. There is no guaranty
		** that this method will be called, especially if the thread has been killed because
		** it did not stop before the timeout was reached.
		*/
		virtual void onStopped() {}


	private:
		//! Merely calls our `onExecute()` event
		virtual void baseExecute() {onExecute();}

	}; // class AThread




} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_ATHREAD_H__
