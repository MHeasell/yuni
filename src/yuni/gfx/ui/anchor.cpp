
#include "control.h"
#include "../../misc/math.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{



	SharedPtr<Control> Control::Anchor::sibling()
	{
		MutexLocker locker(pOwner->pMutex);
		return pSibling;
	}


	void Control::Anchor::borderSpace(const float v, const Unit& u)
	{
		pOwner->pMutex.lock();
		pUnit  = u;
		pValue = Math::MinMax<float>(v, -YUNI_GFX_UI_BORDER_SPACE_MAX, YUNI_GFX_UI_BORDER_SPACE_MAX);
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


	std::pair<float, Unit> Control::Anchor::borderSpace()
	{
		MutexLocker locker(pOwner->pMutex);
		return std::pair<float, Unit>(pValue, pUnit);
	}

	Unit Control::Anchor::borderSpaceUnit()
	{
		MutexLocker locker(pOwner->pMutex);
		return pUnit;
	}


	float Control::Anchor::borderSpaceValue()
	{
		MutexLocker locker(pOwner->pMutex);
		return pValue;
	}


	void Control::Anchor::borderSpaceValue(const float v)
	{
		pOwner->pMutex.lock();
		pValue = v;
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


	void Control::Anchor::borderSpaceUnit(const Unit& u)
	{
		pOwner->pMutex.lock();
		pUnit = u;
		if (!pOwner->pUpdateSessionRefCount)
			pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

