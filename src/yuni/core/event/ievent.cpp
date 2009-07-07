
#include "ievent.h"


namespace Yuni
{
namespace Event
{

	bool IEvent::Exists(const IEvent::List& lst, const IEvent* e)
	{
		const List::const_iterator end = lst.end();
		for (List::const_iterator i = lst.begin(); i != end; ++i)
		{
			if (e == *i)
				return true;
		}
		return false;
	}


	bool IEvent::RemoveFromList(IEvent::List& lst, const IEvent* e)
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



} // namespace Event
} // namespace Yuni
