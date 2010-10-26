#ifndef __YUNI_UI_QUEUESERVICE_HXX__
# define __YUNI_UI_QUEUESERVICE_HXX__


namespace Yuni
{
namespace UI
{


	template<class ChildT>
	inline IQueueService<ChildT>::IQueueService()
	{
	}


	template<class ChildT>
	inline IQueueService<ChildT>::~IQueueService()
	{
		// Ensures all notifiers are no longer linked with this class
		destroyBoundEvents();
	}


	template<class ChildT>
	inline bool IQueueService<ChildT>::onLoop()
	{
		return static_cast<ParentType*>(this)->onLoop();
	}


} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_QUEUESERVICE_HXX__
