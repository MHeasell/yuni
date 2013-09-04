
#include <yuni/yuni.h>
#include <yuni/thread/async.h>
#include <yuni/core/system/suspend.h>
#include <yuni/core/logs.h>

using namespace Yuni;


# ifdef YUNI_HAS_CPP_LAMBDA

int main(void)
{
	// A simple logger, which only display on std::cout/cerr
	Logs::Logger<> logs;

	async([&] () {
		logs.info() << "thread1: some complex computations here...";
		// suspend the execution of the thread for 3 seconds for the demo
		Suspend(3);
		logs.info() << "thread1: done here !";
	});

	async([&] () {
		logs.info() << "thread2: some complex computations here...";
		// suspend the execution of the thread for 2 seconds for the demo
		Suspend(2);
		logs.info() << "thread2: done here !";
	});

	return 0;
}




# else

// here is an example for compilers which do not support c++11 features


// A simple logger, which only display on std::cout/cerr
static Logs::Logger<> logs;


static void Thread1Callback()
{
	logs.info() << "thread1: some complex computations here...";
	// block the execution of the thread for 3 seconds for the demo
	Suspend(3);
	logs.info() << "thread1: done here !";
}

static void Thread2Callback()
{
	logs.info() << "thread2: some complex computations here...";
	// block the execution of the thread for 2 seconds for the demo
	Suspend(2);
	logs.info() << "thread2: done here !";
}


int main(void)
{
	Thread::IThread::Ptr thread1 = async(& Thread1Callback);
	Thread::IThread::Ptr thread2 = async(& Thread2Callback);

	thread1->wait(); // wait for the first thread
	thread2->wait(); // wait for the second thread
	return 0;
}



# endif
