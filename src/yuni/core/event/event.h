#ifndef __YUNI_CORE_EVENT_EVENT_H__
# define __YUNI_CORE_EVENT_EVENT_H__

# include "../../yuni.h"
# include <list>
# include "../../threads/policy.h"
# include "event.declaration.h"
# include "ievent.h"
# include "observer/observer.h"
# include "observer/item.h"



namespace Yuni
{

/*!
** \brief Events
** \ingroup Events
*/
namespace Event
{


	/*!
	** \todo Implement several methods for executing the event
	*/
	class Immediate
	{
	};





	/*!
	** \brief Event with no parameter
	**
	** \tparam R Type of the returned value
	** \tparam TP The threading policy
	*/
	template<class R, template<class> class TP>
	class E0 : public TP<E0<R, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E0<R, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA0<R>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E0();
		//! Destructor
		virtual ~E0();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)());

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () ();

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E0





	/*!
	** \brief Event with a single parameter
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, template<class> class TP>
	class E1 : public TP<E1<R, A0, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E1<R, A0, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA1<R, A0>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E1();
		//! Destructor
		virtual ~E1();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E1





	/*!
	** \brief Event with 2 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, template<class> class TP>
	class E2 : public TP<E2<R, A0, A1, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E2<R, A0, A1, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA2<R, A0, A1>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E2();
		//! Destructor
		virtual ~E2();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E2





	/*!
	** \brief Event with 3 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, template<class> class TP>
	class E3 : public TP<E3<R, A0, A1, A2, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E3<R, A0, A1, A2, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA3<R, A0, A1, A2>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E3();
		//! Destructor
		virtual ~E3();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E3





	/*!
	** \brief Event with 4 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, template<class> class TP>
	class E4 : public TP<E4<R, A0, A1, A2, A3, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E4<R, A0, A1, A2, A3, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA4<R, A0, A1, A2, A3>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E4();
		//! Destructor
		virtual ~E4();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E4





	/*!
	** \brief Event with 5 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, template<class> class TP>
	class E5 : public TP<E5<R, A0, A1, A2, A3, A4, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E5<R, A0, A1, A2, A3, A4, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA5<R, A0, A1, A2, A3, A4>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E5();
		//! Destructor
		virtual ~E5();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E5





	/*!
	** \brief Event with 6 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, template<class> class TP>
	class E6 : public TP<E6<R, A0, A1, A2, A3, A4, A5, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E6<R, A0, A1, A2, A3, A4, A5, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA6<R, A0, A1, A2, A3, A4, A5>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E6();
		//! Destructor
		virtual ~E6();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E6





	/*!
	** \brief Event with 7 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, template<class> class TP>
	class E7 : public TP<E7<R, A0, A1, A2, A3, A4, A5, A6, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E7<R, A0, A1, A2, A3, A4, A5, A6, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA7<R, A0, A1, A2, A3, A4, A5, A6>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E7();
		//! Destructor
		virtual ~E7();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E7





	/*!
	** \brief Event with 8 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, template<class> class TP>
	class E8 : public TP<E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E8<R, A0, A1, A2, A3, A4, A5, A6, A7, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA8<R, A0, A1, A2, A3, A4, A5, A6, A7>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E8();
		//! Destructor
		virtual ~E8();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E8





	/*!
	** \brief Event with 9 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, template<class> class TP>
	class E9 : public TP<E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E9();
		//! Destructor
		virtual ~E9();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E9





	/*!
	** \brief Event with 10 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, template<class> class TP>
	class E10 : public TP<E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E10();
		//! Destructor
		virtual ~E10();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E10





	/*!
	** \brief Event with 11 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, template<class> class TP>
	class E11 : public TP<E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E11();
		//! Destructor
		virtual ~E11();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E11





	/*!
	** \brief Event with 12 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam A11 Type of the 12th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, template<class> class TP>
	class E12 : public TP<E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E12();
		//! Destructor
		virtual ~E12();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E12





	/*!
	** \brief Event with 13 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam A11 Type of the 12th argument
	** \tparam A12 Type of the 13th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, template<class> class TP>
	class E13 : public TP<E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E13();
		//! Destructor
		virtual ~E13();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E13





	/*!
	** \brief Event with 14 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam A11 Type of the 12th argument
	** \tparam A12 Type of the 13th argument
	** \tparam A13 Type of the 14th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, template<class> class TP>
	class E14 : public TP<E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E14();
		//! Destructor
		virtual ~E14();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E14





	/*!
	** \brief Event with 15 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam A11 Type of the 12th argument
	** \tparam A12 Type of the 13th argument
	** \tparam A13 Type of the 14th argument
	** \tparam A14 Type of the 15th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, template<class> class TP>
	class E15 : public TP<E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E15();
		//! Destructor
		virtual ~E15();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E15





	/*!
	** \brief Event with 16 parameters
	**
	** \tparam R Type of the returned value
	** \tparam A0 Type of the 1th argument
	** \tparam A1 Type of the 2th argument
	** \tparam A2 Type of the 3th argument
	** \tparam A3 Type of the 4th argument
	** \tparam A4 Type of the 5th argument
	** \tparam A5 Type of the 6th argument
	** \tparam A6 Type of the 7th argument
	** \tparam A7 Type of the 8th argument
	** \tparam A8 Type of the 9th argument
	** \tparam A9 Type of the 10th argument
	** \tparam A10 Type of the 11th argument
	** \tparam A11 Type of the 12th argument
	** \tparam A12 Type of the 13th argument
	** \tparam A13 Type of the 14th argument
	** \tparam A14 Type of the 15th argument
	** \tparam A15 Type of the 16th argument
	** \tparam TP The threading policy
	*/
	template<class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, template<class> class TP>
	class E16 : public TP<E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E16();
		//! Destructor
		virtual ~E16();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E16






} // namespace Event
} // namespace Yuni

# include "event.hxx"
# include "event.undef.h"

#endif // __YUNI_CORE_EVENT_OBSERVER_ITEM_H__
