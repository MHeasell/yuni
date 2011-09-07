
#include "job.h"


namespace Yuni
{
namespace Edalene
{
namespace Dox2Article
{
namespace Job
{

	namespace // anonymous
	{

		static Yuni::Atomic::Int<>  gJobCount = 0;

	} // anonymous

	Yuni::Job::QueueService<>  queueService;






	bool QueueServiceIsEmpty()
	{
		return !gJobCount;
	}



	IJob::IJob()
	{
		++gJobCount;
	}


	IJob::~IJob()
	{
		--gJobCount;
	}




} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni


