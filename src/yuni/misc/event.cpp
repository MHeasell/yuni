
#include <assert.h>
#include "event.h"



namespace Yuni
{
namespace Event
{


	void Receiver::connectEventNotifier(Notifier* n)
	{
		assert(NULL != n);
		pMutex.lock();
		pNotifiers.insert(n);
		pMutex.unlock();
	}


	void Receiver::disconnectEventNotifier(Notifier* n)
	{
		assert(NULL != n);
		pMutex.lock();
		pNotifiers.erase(n);
		pMutex.unlock();
	}


	void Receiver::disconnectAllNotifiers()
	{
		pMutex.lock();
		disconnectAllNotifiersWL();
		pMutex.unlock();
	}


	void Receiver::disconnectAllNotifiersWL()
	{
		if (!pNotifiers.empty())
		{
			std::set<Notifier*> copy(pNotifiers);
			pNotifiers.clear();
			for (std::set<Notifier*>::const_iterator i = copy.begin(); i != copy.end(); ++i)
				(*i)->disconnect(this, false);
		}
	}


} // namespace Event
} // namespace Yuni


