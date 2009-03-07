
#include "component.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	AComponent::AComponent()
		:pState(csReady), pName()
	{}


	AComponent::~AComponent()
	{
		// Make sure all disconnections are done
		if (pState != csDestroying)
			onBeforeDestructionWL();
	}

	bool AComponent::destroying()
	{
		MutexLocker locker(*this);
		return onBeforeDestructionWL();
	}


	bool AComponent::onBeforeDestructionWL()
	{
		if (pState == csDestroying) // already done, nothing to do
			return false;

		// The state has just changed
		pState = csDestroying;

		// Disconnect all notifiers
		destroyingObserver();

		return true;
	}


	String AComponent::name()
	{
		MutexLocker locker(*this);
		return pName;
	}

	void AComponent::name(const String& n)
	{
		pMutex.lock();
		if (csDestroying != pState)
			pName = n;
		pMutex.unlock();
	}


	AComponent::State AComponent::state()
	{
		MutexLocker locker(*this);
		return pState;
	}


	bool AComponent::ready()
	{
		MutexLocker locker(*this);
		return (pState == csReady);
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

