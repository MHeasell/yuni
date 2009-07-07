#ifndef __YUNI_CORE_EVENT_EVENT_INTERFACE_H__
# define __YUNI_CORE_EVENT_EVENT_INTERFACE_H__

# include <vector>


namespace Yuni
{
namespace Event
{
	// Forward declaration (see observer.h)
	class IObserver;



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
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		IEvent();
		//! Destructor
		virtual ~IEvent();
		//@}

	private:
		// The base class observer is our friend
		template<class D, template<class> class U> friend class Observer;

		/*!
		** \brief Get if an event exists in a given list
		**
		** \param lst A list
		** \param e An event to find in the list
		** \return True if the list contains the event
		*/
		static bool Exists(const List& lst, const IEvent* e);

		/*!
		** \brief Remove an event from a given list
		**
		** \param lst A list
		** \param e An event to remove from the list
		** \return True if the event has been removed from the list
		*/
		static bool RemoveFromList(List& lst, const IEvent* e);

	protected:
		/*!
		** \brief Detach a remove observer
		*/
		virtual void internalDetachObserver(const IObserver* o) = 0;

	}; // class IEvent




} // namespace Event
} // namespace Yuni

# include "ievent.hxx"

#endif // __YUNI_CORE_EVENT_EVENT_INTERFACE_H__
