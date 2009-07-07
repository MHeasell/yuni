#ifndef __YUNI_CORE_EVENT_EVENT_HXX__
# define __YUNI_CORE_EVENT_EVENT_HXX__



namespace Yuni
{
namespace Event
{


	template<class R, template<class> class TP>
	inline E0<R, TP>::E0()
	{}


	template<class R, template<class> class TP>
	inline E0<R, TP>::~E0()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, template<class> class TP>
	template<class C>
	void
	E0<R, TP>::connect(C* observer, R (C::*method)())
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA0<C,Immediate,R>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, template<class> class TP>
	void
	E0<R, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, template<class> class TP>
	void
	E0<R, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, template<class> class TP>
	void
	E0<R, TP>::execute()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent();
		}
	}


	template<class R, template<class> class TP>
	void
	E0<R, TP>::operator () ()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent();
		}
	}


	template<class R, template<class> class TP>
	bool
	E0<R, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, template<class> class TP>
	inline void
	E0<R, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, template<class> class TP>
	inline E1<R, A0, TP>::E1()
	{}


	template<class R, typename A0, template<class> class TP>
	inline E1<R, A0, TP>::~E1()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, template<class> class TP>
	template<class C>
	void
	E1<R, A0, TP>::connect(C* observer, R (C::*method)(A0))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA1<C,Immediate,R, A0>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, template<class> class TP>
	void
	E1<R, A0, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, template<class> class TP>
	void
	E1<R, A0, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, template<class> class TP>
	void
	E1<R, A0, TP>::execute(A0 a0)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0);
		}
	}


	template<class R, typename A0, template<class> class TP>
	void
	E1<R, A0, TP>::operator () (A0 a0)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0);
		}
	}


	template<class R, typename A0, template<class> class TP>
	bool
	E1<R, A0, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, template<class> class TP>
	inline void
	E1<R, A0, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	inline E2<R, A0, A1, TP>::E2()
	{}


	template<class R, typename A0, typename A1, template<class> class TP>
	inline E2<R, A0, A1, TP>::~E2()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	template<class C>
	void
	E2<R, A0, A1, TP>::connect(C* observer, R (C::*method)(A0, A1))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA2<C,Immediate,R, A0, A1>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	void
	E2<R, A0, A1, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	void
	E2<R, A0, A1, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	void
	E2<R, A0, A1, TP>::execute(A0 a0, A1 a1)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1);
		}
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	void
	E2<R, A0, A1, TP>::operator () (A0 a0, A1 a1)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1);
		}
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	bool
	E2<R, A0, A1, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, template<class> class TP>
	inline void
	E2<R, A0, A1, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	inline E3<R, A0, A1, A2, TP>::E3()
	{}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	inline E3<R, A0, A1, A2, TP>::~E3()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	template<class C>
	void
	E3<R, A0, A1, A2, TP>::connect(C* observer, R (C::*method)(A0, A1, A2))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA3<C,Immediate,R, A0, A1, A2>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	void
	E3<R, A0, A1, A2, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	void
	E3<R, A0, A1, A2, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	void
	E3<R, A0, A1, A2, TP>::execute(A0 a0, A1 a1, A2 a2)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2);
		}
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	void
	E3<R, A0, A1, A2, TP>::operator () (A0 a0, A1 a1, A2 a2)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2);
		}
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	bool
	E3<R, A0, A1, A2, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	inline void
	E3<R, A0, A1, A2, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	inline E4<R, A0, A1, A2, A3, TP>::E4()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	inline E4<R, A0, A1, A2, A3, TP>::~E4()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	template<class C>
	void
	E4<R, A0, A1, A2, A3, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA4<C,Immediate,R, A0, A1, A2, A3>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	void
	E4<R, A0, A1, A2, A3, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	void
	E4<R, A0, A1, A2, A3, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	void
	E4<R, A0, A1, A2, A3, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	void
	E4<R, A0, A1, A2, A3, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	bool
	E4<R, A0, A1, A2, A3, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	inline void
	E4<R, A0, A1, A2, A3, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	inline E5<R, A0, A1, A2, A3, A4, TP>::E5()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	inline E5<R, A0, A1, A2, A3, A4, TP>::~E5()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	template<class C>
	void
	E5<R, A0, A1, A2, A3, A4, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA5<C,Immediate,R, A0, A1, A2, A3, A4>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	void
	E5<R, A0, A1, A2, A3, A4, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	void
	E5<R, A0, A1, A2, A3, A4, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	void
	E5<R, A0, A1, A2, A3, A4, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	void
	E5<R, A0, A1, A2, A3, A4, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	bool
	E5<R, A0, A1, A2, A3, A4, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	inline void
	E5<R, A0, A1, A2, A3, A4, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	inline E6<R, A0, A1, A2, A3, A4, A5, TP>::E6()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	inline E6<R, A0, A1, A2, A3, A4, A5, TP>::~E6()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	template<class C>
	void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA6<C,Immediate,R, A0, A1, A2, A3, A4, A5>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	bool
	E6<R, A0, A1, A2, A3, A4, A5, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	inline void
	E6<R, A0, A1, A2, A3, A4, A5, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	inline E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::E7()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	inline E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::~E7()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	template<class C>
	void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA7<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	bool
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	inline void
	E7<R, A0, A1, A2, A3, A4, A5, A6, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	inline E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::E8()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	inline E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::~E8()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	template<class C>
	void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA8<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	bool
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	inline void
	E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	inline E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::E9()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	inline E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::~E9()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	template<class C>
	void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA9<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	bool
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	inline void
	E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	inline E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::E10()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	inline E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::~E10()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	template<class C>
	void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA10<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	bool
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	inline void
	E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	inline E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::E11()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	inline E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::~E11()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	template<class C>
	void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA11<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	bool
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	inline void
	E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	inline E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::E12()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	inline E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::~E12()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	template<class C>
	void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA12<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	bool
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	inline void
	E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	inline E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::E13()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	inline E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::~E13()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	template<class C>
	void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA13<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	bool
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	inline void
	E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	inline E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::E14()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	inline E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::~E14()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	template<class C>
	void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA14<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	bool
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	inline void
	E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	inline E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::E15()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	inline E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::~E15()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	template<class C>
	void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA15<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	bool
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	inline void
	E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	inline E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::E16()
	{}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	inline E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::~E16()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	template<class C>
	void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA16<C,Immediate,R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				((*i)->observer())->internalDetachEvent(this);
			pObservers.clear();
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
		}
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	bool
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	inline void
	E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}





} // namespace Event
} // namespace Yuni

#endif // __YUNI_CORE_EVENT_OBSERVER_ITEM_HXX__
