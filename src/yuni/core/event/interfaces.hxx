#ifndef __YUNI_CORE_EVENT_INTERFACES_HXX__
# define __YUNI_CORE_EVENT_INTERFACES_HXX__

# include "../../yuni.h"
# include <list>
# include <assert.h>


namespace Yuni
{


	template<class Derived, template<class> class TP>
	inline IEventObserver<Derived,TP>::IEventObserver()
		:pBoundEventTable(new IEvent::Map())
	{}


	template<class Derived, template<class> class TP>
	inline IEventObserver<Derived,TP>::~IEventObserver()
	{
		// The derived class must remove the boumd events itself
		// to prevent race data and a corrupt vtable
		assert(NULL == pBoundEventTable
			&& "IEventObserver: The derived class must call `destroyBoundEvents()` by itself to prevent a corrupt vtable when destroying the object");
	}


	template<class Derived, template<class> class TP>
	void IEventObserver<Derived,TP>::boundEventIncrementReference(IEvent* evt)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pBoundEventTable)
			++((*pBoundEventTable)[evt]);
	}


	template<class Derived, template<class> class TP>
	void IEventObserver<Derived,TP>::boundEventDecrementReference(IEvent* evt)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pBoundEventTable && !pBoundEventTable->empty())
		{
			IEvent::Map::iterator i = pBoundEventTable->find(evt);
			if (i != pBoundEventTable->end())
			{
				if (i->second <= 1)
				{
					// We won't keep IEvent with no reference
					pBoundEventTable->erase(i);
				}
				else
				{
					// Decrementing the reference count
					--(i->second);
				}
			}
		}
	}


	template<class Derived, template<class> class TP>
	void IEventObserver<Derived,TP>::boundEventRemoveFromTable(IEvent* evt)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pBoundEventTable && !pBoundEventTable->empty())
		{
			IEvent::Map::iterator i = pBoundEventTable->find(evt);
			if (i != pBoundEventTable->end())
				pBoundEventTable->erase(i);
		}
	}


	template<class Derived, template<class> class TP>
	void IEventObserver<Derived,TP>::destroyBoundEvents()
	{
		IEvent::Map* events;
		{
			// Getting the pointer to the table of bound events
			// to unlock the mutex as soon as possible
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pBoundEventTable)
				return;
			events = pBoundEventTable;
			// As this variable is set to NULL, bound events will be disabled
			// It will prevent against further attempts of connection while
			// the object is being destroyed
			pBoundEventTable = NULL;
		}
		// Disconnection all events
		if (!events->empty())
		{
			const IEvent::Map::iterator end = pBoundEventTable->end();
			for (IEvent::Map::iterator i = pBoundEventTable->begin(); i != end; ++i)
				i->first->unregisterObserver(this);
		}
		// Destroying the table
		delete events;
	}



} // namespace Yuni

#endif // __YUNI_CORE_EVENT_INTERFACES_HXX__
