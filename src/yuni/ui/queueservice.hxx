#ifndef __YUNI_UI_QUEUESERVICE_HXX__
# define __YUNI_UI_QUEUESERVICE_HXX__

#include <iostream>

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
		typename ThreadingPolicy::MutexLocker lock(*this);

		if (!(!pDesktop))
			pDesktop->disconnect();
		// Ensures all notifiers are no longer linked with this class
		EventObserverType::destroyBoundEvents();
	}


	template<class ChildT>
	inline Desktop::Ptr IQueueService<ChildT>::desktop() const
	{
		typename ThreadingPolicy::MutexLocker lock(*this);
		return pDesktop;
	}


	template<class ChildT>
	inline void IQueueService<ChildT>::desktop(Desktop::Ptr newDesktop)
	{
		typename ThreadingPolicy::MutexLocker lock(*this);
		if (!(!pDesktop))
			pDesktop->disconnect();
		pDesktop = newDesktop;
		// Reconnect desktop events
		pDesktop->onShowWindow.connect(this, &IQueueService<ChildT>::showWindow);
		pDesktop->onHideWindow.connect(this, &IQueueService<ChildT>::hideWindow);
		pDesktop->onCloseWindow.connect(this, &IQueueService<ChildT>::closeWindow);
		pDesktop->onShowComponent.connect(this, &IQueueService<ChildT>::showComponent);
		pDesktop->onHideComponent.connect(this, &IQueueService<ChildT>::hideComponent);
		pDesktop->onUpdateComponent.connect(this, &IQueueService<ChildT>::updateComponent);

		// Also tell it to reconnect its applications
		pDesktop->reconnect();
	}


	template<class ChildT>
	inline void IQueueService<ChildT>::showWindow(const Application::GUID& appID, Window::Ptr window)
	{
		RequestType delegate;
		typename ShowWindowParams::Ptr params = new ShowWindowParams(appID, window);
		ChildType* thisAsChild = static_cast<ChildType*>(this);

		delegate.bind(thisAsChild, &ChildType::showWindowDispatched, params);
		dynamic_cast<EventLoopType*>(this)->dispatch(delegate);
	}

	template<class ChildT>
	inline void IQueueService<ChildT>::hideWindow(const Application::GUID& appID, const IComponent::ID& windowID)
	{
		hideWindow(appID, windowID);
	}

	template<class ChildT>
	inline void IQueueService<ChildT>::closeWindow(const Application::GUID& appID, const IComponent::ID& windowID)
	{
		// TODO
	}

	template<class ChildT>
	inline void IQueueService<ChildT>::showComponent(const Application::GUID& appID, IComponent::Ptr component)
	{}

	template<class ChildT>
	inline void IQueueService<ChildT>::hideComponent(const Application::GUID& appID, const IComponent::ID& componentID)
	{}

	template<class ChildT>
	inline void IQueueService<ChildT>::updateComponent(const Application::GUID& appID, const IComponent::ID& componentID)
	{}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_QUEUESERVICE_HXX__
