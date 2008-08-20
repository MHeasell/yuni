
#include <yuni/threads/thread.h>
#include <yuni/threads/abstract.thread.h>
#include <assert.h>


namespace Yuni
{
namespace Threads
{


    Abstract::Abstract()
        :Private::AbstractThreadModel()
    {}

    Abstract::~Abstract()
    {
        assert(isRunning() == false);
    }


} // namespace Threads
} // namespace Yuni

