
#include "control.h"
#include "../core/math.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{



	SharedPtr<Control> Control::Anchor::sibling()
	{
		Control::MutexLocker locker(*pOwner);
		return pSibling;
	}


	void Control::Anchor::reset(const float v, const Unit& u /* = unPercent */)
	{
		pOwner->pMutex.lock();
		// Set the new unit
		pUnit  = u;
		// Set the new distance
		setNewValueWL(v);
		// Force update
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


	std::pair<float, Unit> Control::Anchor::get()
	{
		Control::MutexLocker locker(*pOwner);
		return std::pair<float, Unit>(pValue, pUnit);
	}

	Unit Control::Anchor::unit()
	{
		Control::MutexLocker locker(*pOwner);
		return pUnit;
	}


	float Control::Anchor::distance()
	{
		Control::MutexLocker locker(*pOwner);
		return pValue;
	}


	void Control::Anchor::setNewValueWL(const float newV)
	{
		// Whatever the unit, we can use the following check :
		pValue = Math::MinMax<float>(newV, -YUNI_GFX_UI_BORDER_SPACE_MAX, YUNI_GFX_UI_BORDER_SPACE_MAX);
		// Obviously, a percent of the size of the screen > 1 might not be really
		// usefull but it is possible
	}


	void Control::Anchor::distance(const float v)
	{
		pOwner->pMutex.lock();
		setNewValueWL(v);
		// Force update
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


	void Control::Anchor::unit(const Unit& u)
	{
		pOwner->pMutex.lock();
		// Assign the new unit
		pUnit = u;
		// Verify that the stored value is still valid with the new unit
		setNewValueWL(pValue);
		// Force update
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}



} // namespace UI
} // namespace Gfx
} // namespace Yuni

