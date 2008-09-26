
#include "control.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{



	Control::~Control()
	{
		beginUpdateWL();
		if (pState != csDestroying)
			destroying();
		// Delete all children
		clear();
		endUpdateWL();
	}
		
	bool Control::onBeforeDestructionWL()
	{
		if (Component::onBeforeDestructionWL())
		{
			// Prevent this control from drawing
			pUpdateSessionRefCount = LONG_MAX;

			// Disconnect all anchors
			anchors[Anchor::akLeft].resetSiblingWL();
			anchors[Anchor::akTop].resetSiblingWL();
			anchors[Anchor::akRight].resetSiblingWL();
			anchors[Anchor::akBottom].resetSiblingWL();
			return true;
		}
		return false;
	}
	
	void Control::internalCachePosSizeUpdateWL()
	{
		if (!pUpdateSessionRefCount)
		{
			pCacheBounds.reset(pPosition.x, pPosition.y, pPosition.x + pSize.x, pPosition.y + pSize.y);
		}
	}
	
	Rect2D<float> Control::bounds()
	{
		MutexLocker locker(pMutex);
		return pCacheBounds;
	}

	void Control::bounds(Rect2D<float> r)
	{
		r.repair();
		pMutex.lock();
		pPosition.x = r.x1;
		pPosition.y = r.y1;
		pSize.x = r.x2 - r.x1;
		pSize.y = r.y2 - r.y1;
		if (!pUpdateSessionRefCount)
		{
			internalCachePosSizeUpdateWL();
			invalidateWL();
		}
		pMutex.unlock();
	}

	Point2D<float> Control::position()
	{
		MutexLocker locker(pMutex);
		return pPosition;
	}

	void Control::position(const Point2D<float>& np)
	{
		pMutex.lock();
		pPosition = np;
		if (!pUpdateSessionRefCount)
			internalCachePosSizeUpdateWL();
		pMutex.unlock();
	}

	void Control::position(const float x, const float y)
	{
		pMutex.lock();
		pPosition.x = x;
		pPosition.y = y;
		if (!pUpdateSessionRefCount)
			internalCachePosSizeUpdateWL();
		pMutex.unlock();
	}

	
	bool Control::visible()
	{
		MutexLocker locker(pMutex);
		return pVisible;
	}


	void Control::visible(const bool v)
	{
		pMutex.lock();
		pVisible = v;
		invalidateWL();
		pMutex.unlock();
	}
	
	bool Control::enabled()
	{
		MutexLocker locker(pMutex);
		return pEnabled;
	}


	void Control::enabled(const bool v)
	{
		pMutex.lock();
		pEnabled = v;
		invalidateWL();
		pMutex.unlock();
	}

	bool Control::isVisible(const Rect2D<float>& limits)
	{
		MutexLocker locker(pMutex);
		return pVisible && limits.collidedWith(pCacheBounds);
	}
		
	
	Point2D<float> Control::dimensions()
	{
		MutexLocker locker(pMutex);
		return pSize;
	}


	void Control::dimensions(const float w, const float h)
	{
		pMutex.lock();
		pSize.x = w;
		pSize.y = h;
		if (!pUpdateSessionRefCount)
		{
			internalCachePosSizeUpdateWL();
			invalidateWL();
		}
		pMutex.unlock();
	}

	void Control::invalidate()
	{
		pMutex.lock();
		invalidateWL();
		pMutex.unlock();
	}


	void Control::invalidateWL()
	{
		if (!pUpdateSessionRefCount && !pIsInvalidated && csDestroying != pState)
		{
			// TODO Invalidation code here
			pIsInvalidated = true;
			internalCachePosSizeUpdateWL();
		}
	}


	void Control::beginUpdate()
	{
		pMutex.lock();
		++pUpdateSessionRefCount;
		pMutex.unlock();
	}

	void Control::endUpdate()
	{
		pMutex.lock();
		endUpdateWL();
		pMutex.unlock();
	}

	void Control::beginUpdateWL()
	{
		if (!pUpdateSessionRefCount)
		{
			++pUpdateSessionRefCount;
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
				(*i)->beginUpdate();
		}
		else
			++pUpdateSessionRefCount;
	}

	void Control::endUpdateWL()
	{
		if (pUpdateSessionRefCount > 0 && csDestroying != pState)
		{
			--pUpdateSessionRefCount;
			if (!pUpdateSessionRefCount)
			{
				for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
					(*i)->endUpdate();
				invalidateWL();
			}
		}
	}



} // namespace UI
} // namespace Gfx
} // namespace Yuni

