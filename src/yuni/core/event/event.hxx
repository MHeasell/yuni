#ifndef __YUNI_CORE_EVENT_EVENT_HXX__
# define __YUNI_CORE_EVENT_EVENT_HXX__


namespace Yuni
{


	template<typename P>
	inline Event<P>::Event()
	{}


	template<typename P>
	inline Event<P>::Event(const Event<P>& rhs)
	{
		typename ThreadingPolicy::MutexLocker locker(rhs);
	}


	template<typename P>
	inline Event<P>::~Event()
	{
		clear();
	}


	template<typename P>
	void Event<P>::clear()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!AncestorType::pBindList.empty())
		{
			// We will inform all bound objects that we are no longer linked.
			IEvent* baseThis = dynamic_cast<IEvent*>(this);
			const IEventObserverBase* base;
			const typename AncestorType::BindList::iterator end = AncestorType::pBindList.end();
			for (typename AncestorType::BindList::iterator i = AncestorType::pBindList.begin(); i != end; ++i)
			{
				if ((*i).isDescendantOfIEventObserverBase())
				{
					// Getting the object pointer, if any
					base = (const IEventObserverBase*) ((*i).object());
					if (base)
						base->boundEventRemoveFromTable(baseThis);
				}
			}
			// Clear our own list
			AncestorType::pBindList.clear();
		}
	}


	template<typename P>
	void Event<P>::connect(typename BindType::FunctionType pointer)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Bind<P> b;
		b.bind(pointer);
		AncestorType::pBindList.push_back(b);
	}


	template<typename P>
	template<typename U>
	void Event<P>::connect(typename BindType::template WithUserData<U>::FunctionType pointer,
		typename BindType::template WithUserData<U>::ParameterType userdata)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Bind<P> b;
		b.bind(pointer, userdata);
		AncestorType::pBindList.push_back(b);
	}


	template<typename P>
	template<class C>
	void Event<P>::connect(C* o, typename Event<P>::template PointerToMember<C>::Type method)
	{
		if (o)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			Bind<P> b;
			b.bind(o, method);
			assert(b.isDescendantOfIEventObserverBase() && "Invalid class C");
			AncestorType::pBindList.push_back(b);
			(dynamic_cast<const IEventObserverBase*>(o))->boundEventIncrementReference(dynamic_cast<IEvent*>(this));
		}
	}


	template<typename P>
	template<class C>
	void Event<P>::connect(const C* o, typename Event<P>::template PointerToMember<C>::ConstType method)
	{
		if (o)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			Bind<P> b;
			b.bind(o, method);
			assert(b.isDescendantOfIEventObserverBase() && "Invalid class C");
			AncestorType::pBindList.push_back(b);
			(dynamic_cast<const IEventObserverBase*>(o))->boundEventIncrementReference(dynamic_cast<IEvent*>(this));
		}
	}


	template<typename P>
	template<class U>
	void Event<P>::remove(const U* object)
	{
		if (object)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!AncestorType::pBindList.empty())
			{
				typedef Private::EventImpl::template PredicateRemove<U, typename AncestorType::BindType> RemoveType;
				AncestorType::pBindList.remove(RemoveType(dynamic_cast<IEvent*>(this), object));
			}
		}
	}


	template<typename P>
	void Event<P>::unregisterObserver(const IEventObserverBase* pointer)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		// When unregistering an observer, we have to remove it without any more checks
		if (!AncestorType::pBindList.empty())
		{
			typedef Private::EventImpl::template PredicateRemoveWithoutChecks<typename AncestorType::BindType> RemoveType;
			AncestorType::pBindList.remove(RemoveType(pointer));
		}
	}


	template<typename P>
	template<class U>
	inline Event<P>& Event<P>::operator -= (const U* object)
	{
		remove(object);
		return *this;
	}




} // namespace Yuni

#endif // __YUNI_CORE_EVENT_EVENT_HXX__
