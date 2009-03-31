#ifndef __YUNI_TOOLBOX_EVENT_EVENT_H__
# define __YUNI_TOOLBOX_EVENT_EVENT_H__

# include "../../yuni.h"
# include "../preprocessor/std.h"
# include "../preprocessor/enum.h"
# include <vector>
# include <list>
# include "../policies/threading.h"
# include "event.declaration.h"
# include "event.defines.h"



namespace Yuni
{

/*!
** \brief Events
** \ingroup Events
*/
namespace Event
{



	class Immediate
	{
		template<class C, class R, class A1, class A2>
		static void FireEvent(C* o, R (C::*method)(A1, A2), A1 a1, A2 a2)
		{(o->*method)(a1,a2);}
	};






	/*!
	** \brief Observer (Base class)
	** \ingroup Events
	**
	** Only classes derived from the class `Observer` can pretend to receive
	** signals from an event. This is due to the fact that there is a strong
	** relationship between the emitter and the receiver, to prevent the
	** corruption of pointers.
	**
	** The class uses the CRTP (Curiously recurring template pattern) Idiom to
	** broadcast the good type to the threading policy.
	**
	** The derived class *must* disconnect all event emitters as soon as possible
	** when the instance is being destroyed to avoid race exceptions (the VTable may
	** partially be deleted). The method `destroyingObserver()` prevents any further
	** connection with an event emitter and must always be called at least from the
	** destructor.
	**
	**
	** A complete example using the threading policies :
	** \code
	** #include <iostream>
	** #include <yuni/toolbox/event.h>
	**
	**
	** template<template<class> class TP = Policy::ObjectLevelLockable>
	** class ThermalSensor : public TP<ThermalSensor>
	** {
	** public:
	** 		//! The threading policy
	** 		typedef TP<ThermalSensor>  ThreadingPolicy;
	**
	** public:
	** 		ThermalSensor() :pLastValue(0.) {}
	** 		~ThermalSensor() {}
	**
	** 		Event::E1<void, float, TP> eventOnChanged;
	**
	** 		void update(const float newT)
	** 		{
	** 			{
	** 				typename ThreadingPolicy::MutexLocker locker(*this);
	** 				if (pLastValue - newT < 0.1f)
	** 					pLastValue = newT;
	** 				else
	** 					return;
	** 			}
	** 			onChanged(newT);
	** 		}
	**
	** private:
	** 		float pLastValue;
	** };
	**
	**
	** template<template<class> class TP = Policy::ObjectLevelLockable>
	** class Radiator : Event::Observer<Radiator<TP>, TP>
	** {
	** public:
	** 		//! The threading policy
	** 		typedef TP<ThermalSensor>  ThreadingPolicy;
	**
	** public:
	** 		Radiator(const String& name, const float limit)
	** 			:pName(name), pStarted(false), pLimit(limit)
	** 		{}
	**
	** 		~Radiator()
	** 		{
	** 			destroyingObserver();
	** 		}
	**
	** 		String name()
	** 		{
	** 			typename ThreadingPolicy::MutexLocker locker(*this);
	** 			return pName;
	** 		}
	**
	** 		void start()
	** 		{
	** 			typename ThreadingPolicy::MutexLocker locker(*this);
	** 			if (!pStarted)
	** 			{
	** 				pStarted = true;
	** 				std::cout << "The radiator `" << pName << "` has started." << std::endl;
	** 			}
	** 		}
	**
	** 		void stop()
	** 		{
	** 			typename ThreadingPolicy::MutexLocker locker(*this);
	** 			if (pStarted)
	** 			{
	** 				pStarted = false;
	** 				std::cout << "The radiator `" << pName << "`has stopped." << std::endl;
	** 			}
	** 		}
	** 
	** 		void onTemperatureChanged(float t)
	** 		{
	** 			std::cout << "Temperature: " << t << std::endl;
	** 			checkTemperature(t);
	** 		}
	**
	** 		float limit() const {return pLimit;}
	** 		void limit(const float newL) {pLimit = newL;}
	**
	** private:
	** 		void checkTemperature(float t)
	** 		{
	** 			typename ThreadingPolicy::MutexLocker locker(*this);
	** 			if (t >= pLimit)
	** 			{
	** 				if (pStarted)
	** 					stop();
	** 			}
	** 			else
	** 			{
	** 				if (!pStarted)
	** 					start();
	** 			}
	** 		}
	**
	** private:
	** 		const String pName;
	** 		bool pStarted;
	** 		float pLimit;
	** };
	**
	**
	** int main(void)
	** {
	** 		// Our thermal sensor
	** 		ThermalSensor<> sensor;
	**
	** 		// Our observer
	** 		Radiator<> radiatorA("A", 30.0);
	** 		Radiator<> radiatorB("B", 16.0);
	** 		sensor.eventOnChanged.connect(&radiatorA, &Radiator::onTemperatureChanged);
	** 		sensor.eventOnChanged.connect(&radiatorB, &Radiator::onTemperatureChanged);
	**
	** 		sensor.update(-2.);
	** 		sensor.update(10.1);
	** 		sensor.update(15.9);
	** 		sensor.update(22.7);
	** 		sensor.update(42.);
	**
	** 		return 0;
	** }
	** \endcode
	*/
	template<class D, template<class> class TP = Policy::ObjectLevelLockable>
	class Observer : public TP<D>, public IObserver
	{
		YUNI_EVENT_ALLFRIEND_DECL_E;
	public:
		//! The threading policy
		typedef TP<D>  ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Observer() :pCanObserve(true) {}
		//! Destructor
		virtual ~Observer();
		//@}

	protected:
		/*!
		** \brief Disconnect all event emitters and prevents any further connection
		*/
		void destroyingObserver();

		/*!
		** \brief Disconnect all event emitters, if any
		*/
		void disconnectAllEventEmitters();

		/*!
		** \brief Disconnect an event emitter, if connected to the observer
		**
		** \param event The event to disconnect
		*/
		void disconnectEvent(const IEvent* event);

	private:
		/*!
		** \internal Attach an event emitter without doing anything else
		*/
		virtual void internalAttachEvent(IEvent* evt);

		/*!
		** \internal Detach an event emitter without doing anything else
		*/
		virtual void internalDetachEvent(const IEvent* evt);

	private:
		//! List of events that are linked with the observer
		IEvent::List pEvents;
		//!
		bool pCanObserve;

	}; // class Observer



	/*!
	** \brief Event with no argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam TP The threading policy
	*/
	template<class R, template<class> class TP>
	class E0: public IEvent, public TP< E0<R,TP> >
	{
	public:
		typedef TP< E0<R, TP> >  ThreadingPolicy;
		typedef std::list<IObserverItemA0<R>*> ObserverList;

	public:
		E0()
		{}

		virtual ~E0()
		{
			disconnectAll();
		}

		template<class C>
		void connect(C* observer, R (C::*method)())
		{
			if (observer)
			{
				typename ThreadingPolicy::MutexLocker locker(*this);
				pObservers.push_back(new ObserverItemA0<C, Immediate, R>(observer, method));
				observer->internalAttachEvent(this);
			}
		}

		void disconnect(IObserver* o)
		{
			if (NULL != o && removeFromObserverList(o))
				o->internalDetachEvent(this);
		}

		void disconnectAll()
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

		void execute()
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent();
		}

		void operator () () {execute();}

	private:
		bool removeFromObserverList(const IObserver* o)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pObservers.empty())
			{
				const typename ObserverList::iterator end = pObservers.end();
				typename ObserverList::iterator i = pObservers.begin();
				while (i != end)
				{
					if ((*i)->observer() == o)
					{
						pObservers.erase(i++);
						continue;
					}
					++i;
				}
			}
			return false;
		}

		virtual void internalDetachObserver(const IObserver* o)
		{
			removeFromObserverList(o);
		}

	private:
		ObserverList pObservers;
	};



	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(1);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(2);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(3);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(4);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(5);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(6);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(7);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam A7 Type for the 8th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(8);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam A7 Type for the 8th argument
	** \tparam A8 Type for the 9th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(9);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam A7 Type for the 8th argument
	** \tparam A8 Type for the 9th argument
	** \tparam A9 Type for the 10th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(10);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam A8 Type for the 9th argument
	** \tparam A9 Type for the 10th argument
	** \tparam A10 Type for the 11th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(11);

	/*!
	** \brief Event with a single argument
	** \ingroup Events
	** \tparam R Type for the returned value
	** \tparam A0 Type for the first argument
	** \tparam A1 Type for the second argument
	** \tparam A2 Type for the third argument
	** \tparam A3 Type for the 4th argument
	** \tparam A4 Type for the 5th argument
	** \tparam A5 Type for the 6th argument
	** \tparam A6 Type for the 7th argument
	** \tparam A7 Type for the 8th argument
	** \tparam A8 Type for the 9th argument
	** \tparam A9 Type for the 10th argument
	** \tparam A10 Type for the 11th argument
	** \tparam A11 Type for the 12th argument
	** \tparam TP The threading policy
	*/
	YUNI_EVENT_IMPL(12);




} // namespace Event
} // namespace Yuni

# include "event.hxx"
# include "event.undef.h"

#endif // __YUNI_TOOLBOX_EVENT_EVENT_H__
