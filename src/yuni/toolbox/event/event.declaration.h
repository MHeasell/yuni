#ifndef __YUNI_TOOLBOX_EVENT_EVENT_DECLARATION_H__
# define __YUNI_TOOLBOX_EVENT_EVENT_DECLARATION_H__

# include <vector>
# include <list>
# include "../preprocessor/enum.h"




# define YUNI_EVENT_FRIEND_DECL_E(N) \
	template<class YUNI_JOIN(R,N), YUNI_ENUM(N, class U_ ## N),\
		template<class> class YUNI_JOIN(TP,N)> friend class YUNI_JOIN(E,N)


# define YUNI_EVENT_ALLFRIEND_DECL_E \
	template<class R0, template<class> class TP0> friend class E0; \
	YUNI_EVENT_FRIEND_DECL_E(1);\
	YUNI_EVENT_FRIEND_DECL_E(2);\
	YUNI_EVENT_FRIEND_DECL_E(3);\
	YUNI_EVENT_FRIEND_DECL_E(4);\
	YUNI_EVENT_FRIEND_DECL_E(5);\
	YUNI_EVENT_FRIEND_DECL_E(6);\
	YUNI_EVENT_FRIEND_DECL_E(7);\
	YUNI_EVENT_FRIEND_DECL_E(8);\
	YUNI_EVENT_FRIEND_DECL_E(9);\
	YUNI_EVENT_FRIEND_DECL_E(10);\
	YUNI_EVENT_FRIEND_DECL_E(11);\
	YUNI_EVENT_FRIEND_DECL_E(12);\


	
namespace Yuni
{
namespace Event
{

	template<class Host>
	class SingleThreaded
	{
	public:
		/*!
		** \brief Locks a mutex in the constructor and unlocks it in the destructor.
		*/
		class MutexLocker
		{
		public:
			template<class C> MutexLocker(C&) {}
			~MutexLocker() {}
		}; // class MutexLocker


		/*!
		** \brief A volative type
		*/
		template<typename U> struct Volatile { typedef U Type; };

		//! Get if this policy is thread-safe
		enum { threadSafe = false };

	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		SingleThreaded() {}
		//! Copy constructor
		SingleThreaded(const SingleThreaded&) {}
		//! Destructor
		~SingleThreaded() {}
		//@}

	}; // class SingleThreaded


}
}


	



namespace Yuni
{
namespace Event
{

	class IEvent;
	
	class IObserver;
	
	template<class D, template<class> class TP> class Observer;
	

	
# define YUNI_EVENT_FORWARD_DECL_E(N) \
	template<class R, YUNI_ENUM(N, class A), template<class> class TP = SingleThreaded> class YUNI_JOIN(E,N)

	template<class R, template<class> class TP = SingleThreaded> class E0;
	YUNI_EVENT_FORWARD_DECL_E(1);
	YUNI_EVENT_FORWARD_DECL_E(2);
	YUNI_EVENT_FORWARD_DECL_E(3);
	YUNI_EVENT_FORWARD_DECL_E(4);
	YUNI_EVENT_FORWARD_DECL_E(5);
	YUNI_EVENT_FORWARD_DECL_E(6);
	YUNI_EVENT_FORWARD_DECL_E(7);
	YUNI_EVENT_FORWARD_DECL_E(8);
	YUNI_EVENT_FORWARD_DECL_E(9);
	YUNI_EVENT_FORWARD_DECL_E(10);
	YUNI_EVENT_FORWARD_DECL_E(11);
	YUNI_EVENT_FORWARD_DECL_E(12);
	
# undef YUNI_EVENT_FORWARD_DECL_E




	template<class R, class Dummy = void>
	struct IObserverItemA0
	{
		virtual ~IObserverItemA0() {}
		virtual IObserver* observer() const = 0;
		virtual bool equalsTo(const IObserver* o) const = 0;
		virtual R fireEvent() = 0;
	};
	
	template<class C, class Mode, class R, class Dummy = void>
	class ObserverItemA0 : public IObserverItemA0<R, Dummy>
	{
	public:
		ObserverItemA0(C* o, R (C::*method)(void))
			:pObserver(o), pMethod(method)
		{}
		virtual ~ObserverItemA0() {}

		virtual R fireEvent()
		{
			(pObserver->*pMethod)();
		}

		virtual IObserver* observer() const {return pObserver;}
		virtual bool equalsTo(const IObserver* o) const {return pObserver == o;}

	private:
		C* pObserver;
		R (C::*pMethod)(void);
 	}; // class ObserverItem
	

# define YUNI_EVENT_OBSERVER_IMPL(N) \
	template<class R, YUNI_ENUM(N,class A), class Dummy = void>  \
	struct YUNI_JOIN(IObserverItemA, N) \
	{ \
		virtual ~YUNI_JOIN(IObserverItemA, N)() {} \
		virtual IObserver* observer() const = 0; \
		virtual bool equalsTo(const IObserver* o) const = 0; \
		virtual R fireEvent(YUNI_ENUM_2(N, A, a)) = 0; \
	}; \
	\
	\
	template<class C, class Mode, class R, YUNI_ENUM(N,class A), class Dummy = void> \
	class YUNI_JOIN(ObserverItemA,N) : public YUNI_JOIN(IObserverItemA,N)<R, YUNI_ENUM(N,A), Dummy> \
	{ \
	public: \
		YUNI_JOIN(ObserverItemA,N)(C* o, R (C::*method)( YUNI_ENUM(N, A) )) \
			:pObserver(o), pMethod(method) \
		{} \
		virtual ~YUNI_JOIN(ObserverItemA,N)() {} \
		\
		virtual R fireEvent(YUNI_ENUM_2(N, A, a)) \
		{ \
			(pObserver->*pMethod)( YUNI_ENUM(N,a) ); \
		} \
		\
		virtual IObserver* observer() const {return pObserver;} \
		virtual bool equalsTo(const IObserver* o) const {return pObserver == o;} \
		\
	private: \
		C* pObserver; \
		R (C::*pMethod)( YUNI_ENUM(N, A) ); \
 	} // class ObserverItem
	
	YUNI_EVENT_OBSERVER_IMPL(1);
	YUNI_EVENT_OBSERVER_IMPL(2);
	YUNI_EVENT_OBSERVER_IMPL(3);
	YUNI_EVENT_OBSERVER_IMPL(4);
	YUNI_EVENT_OBSERVER_IMPL(5);
	YUNI_EVENT_OBSERVER_IMPL(6);
	YUNI_EVENT_OBSERVER_IMPL(7);
	YUNI_EVENT_OBSERVER_IMPL(8);
	YUNI_EVENT_OBSERVER_IMPL(9);
	YUNI_EVENT_OBSERVER_IMPL(10);
	YUNI_EVENT_OBSERVER_IMPL(11);
	YUNI_EVENT_OBSERVER_IMPL(12);

# undef YUNI_EVENT_OBSERVER_IMPL



	
	/*!
	** \brief Event (Interface)
	** \ingroup Events
	*/
	class IEvent
	{
	public:
		//! List of event
		typedef std::vector<IEvent*>  List;

	public:
		virtual ~IEvent() {}

	private:
		// The base class observer is our friend
		template<class D, template<class> class U> friend class Observer;

		/*!
		** \brief Get if an event exists in a given list
		*/
		static bool Exists(const List& lst, const IEvent* e)
		{
			const List::const_iterator end = lst.end();
			for (List::const_iterator i = lst.begin(); i != end; ++i)
			{
				if (e == *i)
					return true;
			}
			return false;
		}
		
		static bool RemoveFromList(List& lst, const IEvent* e)
		{
			const List::iterator end = lst.end();
			for (List::iterator i = lst.begin(); i != end; ++i)
			{
				if (e == *i)
				{
					lst.erase(i);
					return true;
				}
			}
			return false;
		}
		
	protected:
		virtual void internalDetachObserver(const IObserver* o) = 0;
	};



	/*!
	** \brief Observer (Interface)
	** \ingroup Events
	*/
	class IObserver
	{
		YUNI_EVENT_ALLFRIEND_DECL_E;
	public:
		virtual ~IObserver() {}
	protected:
		virtual void internalAttachEvent(IEvent* evt) = 0;
		virtual void internalDetachEvent(const IEvent* evt) = 0;

	}; // class IObserver




} // namespace Event
} // namespace Yuni

#endif // __YUNI_TOOLBOX_EVENT_EVENT_DECLARATION_H__
