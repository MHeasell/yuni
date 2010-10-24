
#include "queueservice.h"

namespace Yuni
{
namespace UI
{

	IQueueService::~IQueueService()
	{
		// Ensures all notifiers are no longer linked with this class
		destroyBoundEvents();
	}


} // namespace Application
} // namespace Yuni

