
#include "thread.h"
#include "abstract.thread.h"
#include <assert.h>


namespace Yuni
{
namespace Threads
{


	AThread::AThread()
		:Private::AThreadModel()
	{}

	AThread::~AThread()
	{
		assert(isRunning() == false);
	}


} // namespace Threads
} // namespace Yuni

