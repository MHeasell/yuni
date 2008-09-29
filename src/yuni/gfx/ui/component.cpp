
#include "component.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	Component::Component()
		:Event::Receiver(), pState(csReady), pName()
	{}


	Component::~Component()
	{
		// Make sure all disconnections are done
		if (pState != csDestroying)
			onBeforeDestructionWL();
	}

	bool Component::destroying()
	{
		MutexLocker locker(pMutex);
		return onBeforeDestructionWL();
	}


	bool Component::onBeforeDestructionWL()
	{
		if (pState == csDestroying) // already done, nothing to do
			return false;

		// The state has just changed
		pState = csDestroying;

		// Disconnect all notifiers
		disconnectAllNotifiersWL();

		return true;
	}


	String Component::name()
	{
		MutexLocker locker(pMutex);
		return pName;
	}

	void Component::name(const String& n)
	{
		pMutex.lock();
		if (csDestroying != pState)
			pName = n;
		pMutex.unlock();
	}


	Component::State Component::state()
	{
		MutexLocker locker(pMutex);
		return pState;
	}


	bool Component::ready()
	{
		MutexLocker locker(pMutex);
		return (pState == csReady);
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

