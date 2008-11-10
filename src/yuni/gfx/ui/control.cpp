
#include "control.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	Control::Control()
		:Component(), pChildren(), pParent(), pPosition(), pSize(50, 50),
		pVisible(true), pEnabled(true),
		pIsInvalidate(true), pAutosize(false), pUpdateSessionRefCount(0)
	{
		// Initialize anchors
		anchors[Anchor::akLeft].pOwner = this;
		anchors[Anchor::akTop].pOwner = this;
		anchors[Anchor::akRight].pOwner = this;
		anchors[Anchor::akBottom].pOwner = this;
	}



	Control::~Control()
	{
		if (pState != csDestroying)
		{
			// If the control is not yet aware of its destruction, it's time to inform it
			// However, this statement should never be reached from here
			destroying();
		}
		// Delete all children
		clear();
	}


	bool Control::onBeforeDestructionWL()
	{
		if (Component::onBeforeDestructionWL()) // ask to the ancestor first
		{
			// It is better to detach first this component from its parent
			// In this way, it prevents against unwanted operations on these children, like
			// redrawing or input events for example.
			detachFromParentWL();

			// Prevent this control from drawing
			pUpdateSessionRefCount = INT_MAX;

			// Disconnect all anchors
			anchors[Anchor::akLeft].resetSiblingWL();
			anchors[Anchor::akTop].resetSiblingWL();
			anchors[Anchor::akRight].resetSiblingWL();
			anchors[Anchor::akBottom].resetSiblingWL();

			// Keep posted all children that they will be deleted shortly
			this->broadcastOnBeforeDestructionWL();

			return true;
		}
		return false;
	}
	

	void Control::internalCachePosSizeUpdateWL()
	{
		if (!pUpdateSessionRefCount)
		{
			pCacheBounds.reset(pPosition.x, pPosition.y, pPosition.x + pSize.x, pPosition.y + pSize.y);
			// Make some stuff here...
		}
	}

	
	Rect2D<float> Control::bounds()
	{
		MutexLocker locker(*this);
		return pCacheBounds;
	}

	void Control::bounds(Rect2D<float> r)
	{
		// Ensure the point (x1,y1) is the top-left coordinate
		r.repair();

		// Lock
		pMutex.lock();

		// (x1,y1)
		//    +------------------+
		//    |                  |     |
		//    |                  |   height
		//    |                  |     |
		//    +------------------+
		//    <-- width -->   (x2,y2)
		pPosition.x = r.x1;
		pPosition.y = r.y1;
		pSize.x = r.x2 - r.x1;
		pSize.y = r.y2 - r.y1;
		if (!pUpdateSessionRefCount) // not inside an update
			invalidateWL();

		// unlock
		pMutex.unlock();
	}


	Point2D<float> Control::position()
	{
		MutexLocker locker(*this);
		return pPosition;
	}


	void Control::position(const Point2D<float>& np)
	{
		pMutex.lock();
		pPosition = np;
		if (!pUpdateSessionRefCount) // Not inside an update
			internalCachePosSizeUpdateWL();
		pMutex.unlock();
	}


	void Control::position(const float x, const float y)
	{
		pMutex.lock();
		pPosition.x = x;
		pPosition.y = y;
		if (!pUpdateSessionRefCount) // not inside an update
			internalCachePosSizeUpdateWL();
		pMutex.unlock();
	}

	
	bool Control::visible()
	{
		MutexLocker locker(*this);
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
		MutexLocker locker(*this);
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
		MutexLocker locker(*this);
		return pVisible && limits.collidedWith(pCacheBounds);
	}
		
	
	Point2D<float> Control::dimensions()
	{
		MutexLocker locker(*this);
		return pSize;
	}


	void Control::dimensions(const float w, const float h)
	{
		pMutex.lock();
		pSize.x = w;
		pSize.y = h;
		if (!pUpdateSessionRefCount)
			invalidateWL();
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
		beginUpdateWL();
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
		if (csDestroying != pState) // if it will be destroyed shortly, we should abort immediately
		{
			if (!pUpdateSessionRefCount)
			{
				++pUpdateSessionRefCount;
				// We have just started an update. We must inform all children they should start
				// an update too
				for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
					(*i)->beginUpdate();
			}
			else
				++pUpdateSessionRefCount;
		}
	}


	void Control::endUpdateWL()
	{
		if (pUpdateSessionRefCount > 0 && csDestroying != pState)
		{
			// Dec the reference count
			--pUpdateSessionRefCount;
			// If equals to 0, we are back to a normal state
			if (!pUpdateSessionRefCount)
			{
				// Back to a normal state, all children should end their update too
				// before we invalidate this control
				for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
					(*i)->endUpdate();
				// Finally the control must be invalidate
				invalidateWL();
			}
		}
	}


	bool Control::autosize()
	{
		MutexLocker locker(*this);
		return pAutosize;
	}


	void Control::autosize(const bool a)
	{
		pMutex.lock();
		if (a != pAutosize)
		{
			pAutosize = a;
			if (!pUpdateSessionRefCount)
				invalidateWL();
		}
		pMutex.unlock();
	}


	void Control::sendToBack()
	{
		pMutex.lock();
		if (csDestroying == pState)
		{
			pMutex.unlock();
			return;
		}
		SharedPtr<Control> prnt(pParent);
		pMutex.unlock();
		if (prnt.valid())
			prnt->internalChildSendToBack(this);
	}


	void Control::internalChildSendToBack(Control* c)
	{
		// Lock
		MutexLocker locker(*this);
		if (csDestroying == pState || NULL == c || pChildren.empty())
			return;

		// Browsing all children to find our control
		Vector::iterator i = pChildren.begin();
		if (i->get() == c) // The first item is our control, nothing to do
			return;
		++i;
		// End of the container
		Vector::iterator end = pChildren.end();
		for (; i != end; ++i)
		{
			if (i->get() == c) // It seems we've found our control
			{
				// Keeping a reference to our component
				SharedPtr<Control> it(*i);
				// Removing the child
				pChildren.erase(i);
				// Inserting it at the begining
				pChildren.insert(pChildren.begin(), it);
				// Invalidate itself
				invalidateWL();
				return;
			}
		}
	}


	void Control::bringToFront()
	{
		pMutex.lock();
		if (csDestroying == pState)
		{
			pMutex.unlock();
			return;
		}
		SharedPtr<Control> prnt(pParent);
		pMutex.unlock();
		if (prnt.valid())
			prnt->internalChildBringToFront(this);
	}


	void Control::internalChildBringToFront(Control* c)
	{
		// Lock
		MutexLocker locker(*this);
		if (pChildren.empty() || csDestroying == pState || NULL == c)
			return;

		// End of the container
		Vector::iterator end = pChildren.end();
		// Browsing all children to find our control
		for (Vector::iterator i = pChildren.begin(); i != end; ++i)
		{
			if (i->get() == c) // It seems we've found our control
			{
				// Keeping a reference to our component
				SharedPtr<Control> it(*i);
				// Removing the child
				pChildren.erase(i);
				// Inserting it at the end
				pChildren.push_back(it);
				// Invalidate itself
				invalidateWL();
				return;
			}
		}
	}

	
	void Control::detachFromParentWL()
	{
		if (pParent.valid())
		{
			// We make sure that we are really disconnected from the parent
			// We suppose here the parent can not be destroyed before ourselves
			Control* prnt = pParent.get();
			pParent.reset();
			// Keep inform the parent that we are no longer one of its children
			prnt->internalUnregisterChild(this);
		}
	}


	void Control::detachFromParent()
	{
		pMutex.lock();
		detachFromParentWL();
		pMutex.unlock();
	}


	bool Control::parent(const SharedPtr<Control>& newParent)
	{
		if (newParent == this) // A component can not be a parent for itself
			return false;

		if (newParent.null() || pState == csDestroying)
		{
			// If the new parent is not valid, to detach this component from the current parent
			// will be faster
			this->detachFromParent();
			// An invalid parent is not managed as an error
			return true;
		}

		// Lock
		MutexLocker locker(*this);
		if (csDestroying == pState)
		{
			// The component is in a destroying state. We should abort as soon as possible
			// A new parent will be useless at this step and the better thing to do
			// is to make sure we no longer belong to a parent
			this->detachFromParent();
			// The operation obviously failed
			return false;
		}
		
		if (pParent.null())
		{
			// This component has never been affected to a shared pointer
			newParent->internalRegisterChild(this);
		}
		else
		{
			// We have to check if the new parent is not one of our children and if it 
			// is not already our parent
			if (pParent == newParent || this->existsChildFromPtrWL(newParent.get(), true))
				return false;

			SharedPtr<Control> myself;
			if (pParent->findChildFromPtr(myself, this, false))
			{
				// Adding myself to the list of children of the new parent
				newParent->internalRegisterChild(myself);
				// Removing myself from the previous parent
				pParent->internalUnregisterChild(this);
			}
			else
				// We can safely add ourselves in the list of children of the new parent
				newParent->internalRegisterChild(this);
		}

		// Ok, we can make have this new parent
		pParent = newParent;
		// Invalidate the control
		invalidateWL();
		
		// Success
		return true;
	}


	bool Control::existsChildFromPtrWL(const void* toFind, const bool recursive)
	{
		if (recursive)
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			{
				if (i->get() == toFind || (*i)->existsChildFromPtr(toFind, recursive))
					return true;
			}
		}
		else
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			{
				if (i->get() == toFind)
					return true;
			}
		}
		return false;
	}


	bool Control::findChildFromPtrWL(SharedPtr<Control>& out, const void* toFind, const bool recursive)
	{
		// End of the container
		Vector::iterator end = pChildren.end();

		// We want to make a recursive search
		if (recursive)
		{
			for (Vector::iterator i = pChildren.begin(); i != end; ++i)
			{
				if (i->get() == toFind)
				{
					out.reset(*i);
					return true;
				}
				// Ask to the child too
				if ((*i)->findChildFromPtr(out, toFind, recursive))
					return true;
			}
		}
		else
		{
			// We only want to find one of out child
			for (Vector::iterator i = pChildren.begin(); i != end; ++i)
			{
				if (i->get() == toFind)
				{
					out.reset(*i);
					return true;
				}
			}
		}
		return false;
	}

	
	bool Control::findChildFromStringWL(SharedPtr<Control>& out, const String& toFind, const bool recursive)
	{
		// End of the container
		Vector::iterator end = pChildren.end();

		// We want to make a recursive search
		if (recursive)
		{
			for (Vector::iterator i = pChildren.begin(); i != end; ++i)
			{
				if ((*i)->name() == toFind)
				{
					out.reset(*i);
					return true;
				}
				// Ask to the child too
				if ((*i)->findChildFromName(out, toFind, recursive))
					return true;
			}
		}
		else
		{
			// We only want to find one of out child
			for (Vector::iterator i = pChildren.begin(); i != end; ++i)
			{
				if ((*i)->name() == toFind)
				{
					out.reset(*i);
					return true;
				}
			}
		}
		return false;
	}



	bool Control::findChildFromName(SharedPtr<Control>& out, const String& toFind, const bool recursive)
	{
		if (toFind.empty())
			return false;
		MutexLocker locker(*this);
		return (csDestroying != pState) && findChildFromStringWL(out, toFind, recursive);
	}


	bool Control::findChildFromPtr(SharedPtr<Control>& out, const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(*this);
			return (csDestroying != pState) && findChildFromPtrWL(out, toFind, recursive);
		}
		return false;
	}


	bool Control::existsChildFromPtr(const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(*this);
			return (csDestroying != pState) && existsChildFromPtrWL(toFind, recursive);
		}
		return false;
	}


	void Control::internalRegisterChild(Control* nc)
	{
		if (nc)
		{
			pMutex.lock();
			pChildren.push_back(SharedPtr<Control>(nc));
			pMutex.unlock();
		}
	}


	void Control::internalRegisterChild(const SharedPtr<Control>& nc)
	{
		if (nc.valid())
		{
			pMutex.lock();
			pChildren.push_back(nc);
			pMutex.unlock();
		}
	}


	void Control::internalUnregisterChild(Control* nc)
	{
		if (nc)
		{
			MutexLocker locker(*this);
			if (!pChildren.empty())
			{
				Vector::iterator end = pChildren.end();
				for (Vector::iterator i = pChildren.begin(); i != end; ++i)
				{
					if (i->get() == nc)
					{
						pChildren.erase(i);
						return;
					}
				} // for ...
			} // !pChildren.empty()
		}
	}
	


	uint32 Control::childrenCount()
	{
		MutexLocker locker(*this);
		return (uint32) pChildren.size();
	}


	SharedPtr<Control> Control::child(const uint32 indx)
	{
		MutexLocker locker(*this);
		return (csDestroying == pState || pChildren.empty() || pChildren.size() >= indx)
			? SharedPtr<Control>()
			: pChildren[indx];
	}


	SharedPtr<Control> Control::operator [] (const String& nm)
	{
		SharedPtr<Control> out;
		this->findChildFromName(out, nm, false);
		return out;
	}



	void Control::clear()
	{
		pMutex.lock();
		if (!pChildren.empty())
		{
			// We make a copy of the list, to avoid manipulations while the list is being emptied
			Control::Vector copy(pChildren);
			// Empty the original one
			pChildren.clear();

			if (pState != csDestroying)
			{
				// Indicates we will destroy them
				// If the state is already set to `csDestroying`, that means the method
				// `broadcastOnBeforeDestructionWL` has already been called by `onBeforeDestructionWL()`
				broadcastOnBeforeDestructionWL();
				// Invalidate this component
				invalidateWL();
			}

			// We can safely unlock here, just before all children are destroyed
			pMutex.unlock();

			// All children will really be destroyed here  (Control::Vector copy)
			// Note: The tool `MutexLocker should not be used here`. We want to be
			// sure of the destruction order
			return;
		}
		pMutex.unlock();
	}




	void Control::broadcastOnBeforeDestructionWL()
	{
		// Message to all children : You will be deleted shortly !
		for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			(*i)->destroying();
	}




} // namespace UI
} // namespace Gfx
} // namespace Yuni

