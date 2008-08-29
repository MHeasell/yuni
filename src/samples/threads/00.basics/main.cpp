#include <yuni/yuni.h>
#include <yuni/threads.h>
#include <iostream>

//! This mutex will serve to synchronize the standard output.
Yuni::Mutex mutex;

/*!
 * \brief This class represents a task that should be executed
 *	in a separate thread. This task is implemented in the execute()
 *	method, and consists here of a sample: counting beer bottles.
 */
class BottleTask : public Yuni::Threads::Abstract
{
public:
	/*!
	 * \brief Our sample constructor.
	 * \param[in] identifier A thread identifier, used only for display
	 *						 purposes
	 */
	BottleTask(int identifier) :Yuni::Threads::Abstract(), x(identifier) {}
	
	virtual ~BottleTask() {stop();}

protected:
	//! The beer-bottle counting implementation itself
   virtual void execute()
   {
	   int i = 99;
       while(true)
       {
		   mutex.lock();
		   std::cout << " ["<< x <<"] " << i-- << " bottles of beer on a wall. Calculating a very complicated thing ..." << std::endl;
		   mutex.unlock();
		   sleep(1);
           if (suspend(0))
               return;
       }
   }

   /*!
	* \brief In this, we just signal to the user that the thread 
	* execution has stopped, but we can also free thread-specific
	* ressources and do general cleanup.
	*/
   virtual void stopTimer()
   {
	   std::cout << " [b] I have been interrupted." << std::endl;
   }

private:
   //! The class can hold the variables of your choice.
   int x;
};

int main(void)
{
	/*
	 * For thread-planning purposes, Yuni provides an indication of
	 * how many CPUs the system has, so you can plan how you will
	 * manage your resources.
	 */
	std::cout << "[M] Your system has " << Yuni::Threads::Abstract::CPUCount()
		<< " logical processor(s)." << std::endl;

	/*
	 * Here we create a new BottleTask with identifier 0 - keep in
	 * mind that this identifier is specific to our sample class.
	 * We can use it as an abstract or specific class, depending
	 * on the way we want to manage it.
	 */
	Yuni::Threads::Abstract * t = new BottleTask(0);
	std::cout << "[M] Starting bottle counting..." << std::endl;

	/*
	 * Start counting bottles.
	 */
	t->start();

	/*
	 * Then we can do all the processing we want, knowing that the
	 * bottle counting task is running in background. But, beware,
	 * because of the mutual access to the standard output, we
	 * should lock a mutex before printing anything on it.
	 */
	mutex.lock();
	std::cout << "[M] Doing some processing here too." << std::endl;
	mutex.unlock();

	// Simulate a long processing
	sleep(5);

	mutex.lock();
	std::cout << "[M] Stopping bottle counting..." << std::endl;
	mutex.unlock();

	/*
	 * We then stop the bottle-counting thread. It will exit as
	 * soon as possible (on its next call to suspend() for example),
	 * but will be killed anyway after a timeout, in this case 4 seconds.
	 */
	t->stop(4);

	// We do not have to use mutexes anymore.
	std::cout << "[M] Thread stopped." << std::endl;

	/*
	 * Delete the thread object.
	 */
	delete t;
	return 0;
}

