
#include <iostream>
#include <yuni/threads/thread.h>
#include <yuni/threads/condition.h>
#include <yuni/core/system/sleep.h>





class MyOwnThread : public Yuni::Threads::AThread
{
public:
	//! \name Constructor & Destructor
	//@{
	//! Default constructor
	MyOwnThread() {}
	//! Destructor
	virtual ~MyOwnThread() {stop();} // Required for Code robustness
	//@}

public:
	//! The condition to wait
	Yuni::Threads::Condition::Ptr condition;

protected:
	virtual void onExecute()
	{
		std::cout << "[thread] Started." << std::endl;

		// Waiting for the condition from the main thread in
		// this example
		condition->wait();

		{
			// Some stuff here
			std::cout << "[thread] Doing some stuff" << std::endl;
		}

		// The mutex used with the condition must always be unlocked
		// after `wait()`
		condition->unlock();

		std::cout << "[thread] Stopped." << std::endl;
	}

}; // class MyOwnThread





int main(void)
{
	// Our condition, which is shared between the two threads
	Yuni::Threads::Condition::Ptr condition = new Yuni::Threads::Condition();
	// A thread, which will wait for our signal
	MyOwnThread thread;
	thread.condition = condition;

	// Starting the thread
	if (!thread.start())
		return 1;

	// Performing a very long operation...
	std::cout << "[main] Performing a long operation (3 seconds)..." << std::endl;
	Yuni::Sleep(3); // seconds
	std::cout << "[main] Done" << std::endl;

	// Notifying our thread that it should do its work
	condition->notify();

	// Waiting for the end of the thread
	thread.stop();

	return 0;
}

