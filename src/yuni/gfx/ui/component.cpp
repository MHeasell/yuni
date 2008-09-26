
#include "component.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{



	Component::~Component()
	{
		// Make sure all disconnections are done
		if (pState != csDestroying)
			onBeforeDestructionWL();
		// Delete all children
		clear();
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

		// It is better to detach first this component from its parent
		// In this way, it prevents against unwanted operations on these children, like
		// redrawing or input events for example.
		detachFromParentWL();

		// Disconnect all notifiers
		disconnectAllNotifiersWL();

		// Keep posted all children that they will be deleted shortly
		this->broadcastOnBeforeDestructionWL();

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

	
	void Component::detachFromParentWL()
	{
		if (pParent.valid())
		{
			Component* prnt = pParent.get();
			pParent.reset();
			prnt->internalUnregisterChild(this);
		}
	}


	void Component::detachFromParent()
	{
		if (pParent.valid()) // avoid unnecessary locks
		{
			pMutex.lock(); // Double check
			detachFromParentWL();
			pMutex.unlock();
		}
	}


	bool Component::parent(const SharedPtr<Component>& newParent)
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
		MutexLocker locker(pMutex);
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

			SharedPtr<Component> myself;
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


	bool Component::existsChildFromPtrWL(const void* toFind, const bool recursive)
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


	bool Component::findChildFromPtrWL(SharedPtr<Component>& out, const void* toFind, const bool recursive)
	{
		if (recursive)
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			{
				if (i->get() == toFind)
				{
					out.reset(*i);
					return true;
				}
				if ((*i)->findChildFromPtr(out, toFind, recursive))
					return true;
			}
		}
		else
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
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

	bool Component::findChildFromStringWL(SharedPtr<Component>& out, const String& toFind, const bool recursive)
	{
		if (recursive)
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			{
				if ((*i)->name() == toFind)
				{
					out.reset(*i);
					return true;
				}
				if ((*i)->findChildFromName(out, toFind, recursive))
					return true;
			}
		}
		else
		{
			for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
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



	bool Component::findChildFromName(SharedPtr<Component>& out, const String& toFind, const bool recursive)
	{
		if (toFind.empty())
			return false;
		MutexLocker locker(pMutex);
		return (csDestroying != pState) && findChildFromStringWL(out, toFind, recursive);
	}


	bool Component::findChildFromPtr(SharedPtr<Component>& out, const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(pMutex);
			return (csDestroying != pState) && findChildFromPtrWL(out, toFind, recursive);
		}
		return false;
	}


	bool Component::existsChildFromPtr(const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(pMutex);
			return (csDestroying != pState) && existsChildFromPtrWL(toFind, recursive);
		}
		return false;
	}


	void Component::internalRegisterChild(Component* nc)
	{
		if (nc)
		{
			pMutex.lock();
			pChildren.push_back(SharedPtr<Component>(nc));
			pMutex.unlock();
		}
	}

	void Component::internalRegisterChild(const SharedPtr<Component>& nc)
	{
		if (nc.valid())
		{
			pMutex.lock();
			pChildren.push_back(nc);
			pMutex.unlock();
		}
	}


	void Component::internalUnregisterChild(Component* nc)
	{
		if (nc)
		{
			pMutex.lock();
			if (!pChildren.empty())
			{
				Vector::iterator end = pChildren.end();
				for (Vector::iterator i = pChildren.begin(); i != end; ++i)
				{
					if (i->get() == nc)
					{
						pChildren.erase(i);
						pMutex.unlock();
						return;
					}
				}
			}
			pMutex.unlock();
		}
	}
	


	uint32 Component::childrenCount()
	{
		MutexLocker locker(pMutex);
		return (uint32) pChildren.size();
	}


	SharedPtr<Component> Component::child(const uint32 indx)
	{
		MutexLocker locker(pMutex);
		return (csDestroying == pState || pChildren.empty() || pChildren.size() >= indx)
			? SharedPtr<Component>()
			: pChildren[indx];
	}


	SharedPtr<Component> Component::operator [] (const String& nm)
	{
		SharedPtr<Component> out;
		this->findChildFromName(out, nm, false);
		return out;
	}



	void Component::clear()
	{
		pMutex.lock();
		if (!pChildren.empty())
		{
			// We make a copy of the list, to avoid manipulations while the list is being emptied
			Component::Vector backup(pChildren);
			// Empty the original one
			pChildren.clear();

			// Indicates we will destroy them
			// If the state is already set to `csDestroying`, that means the method
			// `broadcastOnBeforeDestructionWL` has already been called by `onBeforeDestructionWL()`
			if (pState != csDestroying)
				broadcastOnBeforeDestructionWL();

			// Invalidate this component
			invalidateWL();

			// We can safely unlock here, just before all children are destroyed
			pMutex.unlock();

			// All children will really be destroyed here
			return;
		}
		pMutex.unlock();
	}


	void Component::broadcastOnBeforeDestructionWL()
	{
		// Message to all children : You will be deleted shortly !
		for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
		{
			if (!(*i)->destroying())
				return;
		}
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

