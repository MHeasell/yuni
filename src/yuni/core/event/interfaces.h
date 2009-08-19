#ifndef __YUNI_CORE_EVENT_INTERFACES_H__
# define __YUNI_CORE_EVENT_INTERFACES_H__

# include "../../yuni.h"
# include <map>
# include <assert.h>
# include "../../threads/policy.h"


namespace Yuni
{

	// Forward declarations
	template<class P> class Event;
	class IEvent;
	class IEventObserverBase;
	template<class Derived, template<class> class TP> class IEventObserver;



	/*!
	** \brief
	** \ingroup Events
	*/
	class IEvent
	{
	public:
		//! IEvent list
		typedef std::map<IEvent*, unsigned int> Map;

	public:
		IEvent() {}
		virtual ~IEvent() {}

	protected:
		/*!
		** \brief Unregister an observer
		**
		** This method will remove all delegates linked with the pointer to object.
		** This method should be called by any observer being destroyed.
		** \param pointer Pointer-to-object (can be null)
		** \return True if at least one reference has been removed, False otherwise
		*/
		virtual bool unregisterObserver(const IEventObserverBase* pointer) = 0;

		// Friend
		template<class Derived, template<class> class TP> friend class IEventObserver;

	}; // class IEvent





	class IEventObserverBase
	{
	public:
		IEventObserverBase() {}
		virtual ~IEventObserverBase() {}

	protected:
		/*!
		** \brief Increment a reference count for a given bound event
		**
		** /param evt An event
		*/
		virtual void boundEventIncrementReference(IEvent* evt) = 0;

		/*!
		** \brief Decrementing a reference ocunt for a given bound event
		**
		** If the reference count reaches 0, it will be removed from the table.
		** /param evt An event
		*/
		virtual void boundEventDecrementReference(IEvent* evt) = 0;

		/*!
		** \brief Remove an boundEvent from the table
		**
		** This method is called when the boundEvent is being destroyed.
		** /param evt An event
		*/
		virtual void boundEventRemoveFromTable(IEvent* evt) = 0;

		// Friends
		template<class P> friend class Event;

	}; // class IEventObserverBase




	template<class Derived, template<class> class TP = Policy::ObjectLevelLockable>
	class IEventObserver
		:public IEventObserverBase, public TP<IEventObserver<Derived,TP> >
	{
	public:
		//! Type of the Event observer
		typedef IEventObserver<Derived,TP> IEventObserverType;
		//! The Threading policy
		typedef TP<IEventObserverType> ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		IEventObserver();
		/*!
		** \brief Destructor
		*/
		virtual ~IEventObserver();
		//@}

	protected:
		/*!
		** \brief Destroy all existing and future bound events
		*/
		void destroyBoundEvents();

	private:
		// \see IEventObserverBase::boundEventIncrementReference()
		virtual void boundEventIncrementReference(IEvent* evt);

		// \see IEventObserverBase::boundEventDecrementReference()
		virtual void boundEventDecrementReference(IEvent* evt);

		// \see IEventObserverBase::boundEventRemoveFromTable()
		virtual void boundEventRemoveFromTable(IEvent* evt);

	private:
		/*!
		** \brief List of attached boundEvents to the observer
		**
		** This class will accept any action from any bound event as long as
		** this pointer remains valid (not null). It is important to set this
		** variable to NULL when the class is being destroyed to avoid race
		** conditions with SMP processors.
		*/
		IEvent::Map* pBoundEventTable;

	}; // class IEventObserver





} // namespace Yuni

# include "interfaces.hxx"

#endif // __YUNI_CORE_EVENT_INTERFACES_H__
