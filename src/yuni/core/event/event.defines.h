#ifndef __YUNI_CORE_EVENT_DEFINES_H__
# define __YUNI_CORE_EVENT_DEFINES_H__



# define YUNI_EVENT_IMPL(N) \
	template<class R, YUNI_ENUM(N,class A), template<class> class TP> \
	class YUNI_JOIN(E,N) : public TP< YUNI_JOIN(E,N)<R, YUNI_ENUM(N,A), TP> >, public IEvent \
	{ \
	public: \
		typedef TP< YUNI_JOIN(E,N)<R, YUNI_ENUM(N,A), TP> >  ThreadingPolicy; \
		typedef std::list<YUNI_JOIN(IObserverItemA,N)<R, YUNI_ENUM(N,A)>*> ObserverList; \
		\
	public: \
		YUNI_JOIN(E,N)() \
		{} \
		\
		virtual ~YUNI_JOIN(E,N)() \
		{ \
			disconnectAll(); \
		} \
		\
		template<class C> \
		void connect(C* observer, R (C::*method)(YUNI_ENUM(N,A))) \
		{ \
			if (observer) \
			{ \
				typename ThreadingPolicy::MutexLocker locker(*this); \
				pObservers.push_back(new YUNI_JOIN(ObserverItemA,N)<C, Immediate, R, YUNI_ENUM(N,A)>(observer, method)); \
				observer->internalAttachEvent(this); \
			} \
		} \
		\
		void disconnect(IObserver* o) \
		{ \
			if (NULL != o && removeFromObserverList(o)) \
				o->internalDetachEvent(this); \
		} \
		\
		void disconnectAll() \
		{ \
			typename ThreadingPolicy::MutexLocker locker(*this); \
			if (!pObservers.empty()) \
			{ \
				const typename ObserverList::iterator end = pObservers.end(); \
				for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i) \
					((*i)->observer())->internalDetachEvent(this); \
				pObservers.clear(); \
			} \
		} \
		\
		void execute(YUNI_ENUM_2(N, A, a)) \
		{ \
			typename ThreadingPolicy::MutexLocker locker(*this); \
			const typename ObserverList::iterator end = pObservers.end(); \
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i) \
				(*i)->fireEvent(YUNI_ENUM(N, a)); \
		} \
		\
		void operator () (YUNI_ENUM_2(N, A,a)) {execute(YUNI_ENUM(N,a));} \
		\
	private: \
		bool removeFromObserverList(const IObserver* o) \
		{ \
			typename ThreadingPolicy::MutexLocker locker(*this); \
			if (!pObservers.empty()) \
			{ \
				const typename ObserverList::iterator end = pObservers.end(); \
				typename ObserverList::iterator i = pObservers.begin(); \
				while (i != end) \
				{ \
					if ((*i)->observer() == o) \
					{ \
						pObservers.erase(i++); \
						continue; \
					} \
					++i; \
				} \
			} \
			return false; \
		} \
		\
		virtual void internalDetachObserver(const IObserver* o) \
		{ \
			removeFromObserverList(o); \
		} \
		\
	private: \
		ObserverList pObservers; \
	}




#endif // __YUNI_CORE_EVENT_DEFINES_H__
