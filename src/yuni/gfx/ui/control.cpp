
#include "control.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{



	Control::~Control()
	{
		if (pState != csDestroying)
			onBeforeDestruction();
		// Delete all children
		clear();
	}
	
	void Control::internalCachePosSizeUpdate()
	{
		pCacheBounds.reset(pLeft, pTop, pLeft + pWidth, pTop + pHeight);
	}
	
	Rect2D<int> Control::bounds()
	{
		MutexLocker locker(pMutex);
		return pCacheBounds;
	}

	void Control::bounds(Rect2D<int> r)
	{
		r.repair();
		pMutex.lock();
		pLeft = r.x1;
		pTop = r.y1;
		pWidth = r.x2 - r.x1;
		pHeight = r.y2 - r.y1;
		internalCachePosSizeUpdate();
		internalInvalidate();
		pMutex.unlock();
	}

	Point2D<int> Control::position()
	{
		MutexLocker locker(pMutex);
		return Point2D<int>(pLeft, pTop);
	}

	void Control::position(const Point2D<int>& np)
	{
		pMutex.lock();
		pLeft = np.x;
		pTop = np.y;
		internalCachePosSizeUpdate();
		pMutex.unlock();
	}

	void Control::position(const int x, const int y)
	{
		pMutex.lock();
		pLeft = x;
		pTop = y;
		internalCachePosSizeUpdate();
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
		internalInvalidate();
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
		internalInvalidate();
		pMutex.unlock();
	}

	bool Control::isVisible(const Rect2D<int>& limits)
	{
		MutexLocker locker(pMutex);
		return pVisible && limits.collidedWith(pCacheBounds);
	}
		
	
	Point2D<int> Control::dimensions()
	{
		MutexLocker locker(pMutex);
		return Point2D<int>(pWidth, pHeight);
	}


	void Control::dimensions(const int w, const int h)
	{
		pMutex.lock();
		pWidth = w;
		pHeight = h;
		internalCachePosSizeUpdate();
		internalInvalidate();
		pMutex.unlock();
	}


	void Control::invalidate()
	{
		if (!pIsInvalidated)
		{
			pMutex.lock();
			internalInvalidate();
			pMutex.unlock();
		}
	}


	void Control::internalInvalidate()
	{
		if (!pIsInvalidated)
		{
			// TODO Invalidation code here
			pIsInvalidated = true;
		}
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

