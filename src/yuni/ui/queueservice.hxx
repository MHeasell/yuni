#ifndef __YUNI_UI_QUEUESERVICE_HXX__
# define __YUNI_UI_QUEUESERVICE_HXX__


namespace Yuni
{
namespace UI
{


	inline QueueService::QueueService()
		: pDeviceIsInitialized(false)
	{
	}


	inline QueueService::~QueueService()
	{
		// Ensures all notifiers are no longer linked with this class
		destroyBoundEvents();
	}


	inline Gfx::Device::Ptr QueueService::device() const
	{
		return pLoop.device;
	}


	inline bool QueueService::isDeviceInitialized() const
	{
		return pDeviceIsInitialized;
	}


	inline bool QueueService::toggleFullscreen()
	{
		return pLoop.device->toggleFullscreen();
	}



} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_QUEUESERVICE_HXX__
