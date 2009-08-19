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
	inline void Event<P>::clear()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
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
	inline void Event<P>::connect(const Bind<P>& custom)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		AncestorType::pBindList.push_back(custom);
	}


	template<typename P>
	template<class C>
	void Event<P>::connect(C* o, typename Event<P>::template PointerToMember<C>::Type method)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Bind<P> b;
		b.bind(o, method);
		AncestorType::pBindList.push_back(b);
	}


	template<typename P>
	template<class C>
	void Event<P>::connect(const C* o, typename Event<P>::template PointerToMember<C>::ConstType method)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Bind<P> b;
		b.bind(o, method);
		AncestorType::pBindList.push_back(b);
	}



	template<typename P>
	bool Event<P>::unregisterObserver(const IEventObserverBase* /*pointer*/)
	{
		return true;
	}


} // namespace Yuni

#endif // __YUNI_CORE_EVENT_EVENT_HXX__
