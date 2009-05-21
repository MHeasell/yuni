#ifndef __YUNI_CORE_EVENT_EVENT_HXX__
# define __YUNI_CORE_EVENT_EVENT_HXX__

# include <assert.h>


namespace Yuni
{
namespace Event
{

	template<class D, template<class> class TP>
	inline Observer<D,TP>::~Observer()
	{
		// The derived parent class must call the method `destroyingObserver()`
		// from its destructor
		assert(pCanObserve == false);
	}


	template<class D, template<class> class TP>
	void
	Observer<D,TP>::destroyingObserver()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pCanObserve = false;
		if (!pEvents.empty())
		{
			const IEvent::List::iterator end = pEvents.end();
			for (IEvent::List::iterator i = pEvents.begin(); i != end; ++i)
				(*i)->internalDetachObserver(this);
			pEvents.clear();
		}
	}


	template<class D, template<class> class TP>
	void
	Observer<D,TP>::disconnectAllEventEmitters()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pEvents.empty())
		{
			const IEvent::List::iterator end = pEvents.end();
			for (IEvent::List::iterator i = pEvents.begin(); i != end; ++i)
				(*i)->internalDetachObserver(this);
			pEvents.clear();
		}
	}

	template<class D, template<class> class TP>
	void
	Observer<D,TP>::disconnectEvent(const IEvent* event)
	{
		assert(NULL != event);
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pEvents.empty() && IEvent::RemoveFromList(pEvents, event))
			event->internalDetachObserver(this);
	}


	template<class D, template<class> class TP>
	void
	Observer<D,TP>::internalAttachEvent(IEvent* evt)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pCanObserve && !IEvent::Exists(pEvents, evt))
			pEvents.push_back(evt);
	}

	template<class D, template<class> class TP>
	inline void
	Observer<D,TP>::internalDetachEvent(const IEvent* evt)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		IEvent::RemoveFromList(pEvents, evt);
	}


} // namespace Event
} // namespace Yuni

#endif // __YUNI_CORE_EVENT_EVENT_HXX__
