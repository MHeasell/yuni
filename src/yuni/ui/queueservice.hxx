#ifndef __YUNI_UI_QUEUESERVICE_HXX__
# define __YUNI_UI_QUEUESERVICE_HXX__


namespace Yuni
{
namespace UI
{


	inline IQueueService::IQueueService()
	{
	}


	inline IQueueService::~IQueueService()
	{
		// Ensures all notifiers are no longer linked with this class
		destroyBoundEvents();
	}



} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_QUEUESERVICE_HXX__
