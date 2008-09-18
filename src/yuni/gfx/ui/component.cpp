
#include "component.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{



	Component::~Component()
	{
		if (pState != csDestroying)
			onBeforeDestruction();
		// Delete all children
		clear();
	}

	void Component::destroying()
	{
		pMutex.lock();
		onBeforeDestruction();
		pMutex.unlock();
	}


	bool Component::onBeforeDestruction()
	{
		// Lock
		MutexLocker locker(pMutex);

		if (pState == csDestroying) // already done
			return false;

		// The state has just changed
		pState = csDestroying;

		// Disconnect all notifiers
		internalDisconnectAllNotifiers();

		// It is better to detach first this component from its parent
		// In this way, it prevents against unwanted operations on these children, like
		// redrawing or input events for example.
		internalDetachFromParent();

		// Keep posted all children
		this->broadcastOnBeforeDestruction();

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
		pName = n;
		pMutex.unlock();
	}

	
	void Component::internalDetachFromParent()
	{
		if (pParent.valid()) // Double check
		{
			pParent->internalUnregisterChild(this);
			pParent.reset();
		}
	}


	void Component::detachFromParent()
	{
		if (pParent.valid())
		{
			pMutex.lock();
			internalDetachFromParent();
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
			return true;
		}

		// Lock
		MutexLocker locker(pMutex);
		if (pState == csDestroying)
		{
			this->detachFromParent();
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
			if (pParent == newParent || this->internalExistsChildFromPtr(newParent.get(), true))
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
		// Success
		return true;
	}


	bool Component::internalExistsChildFromPtr(const void* toFind, const bool recursive)
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


	bool Component::internalFindChildFromPtr(SharedPtr<Component>& out, const void* toFind, const bool recursive)
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

	bool Component::internalFindChildFromString(SharedPtr<Component>& out, const String& toFind, const bool recursive)
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
		return this->internalFindChildFromString(out, toFind, recursive);
	}


	bool Component::findChildFromPtr(SharedPtr<Component>& out, const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(pMutex);
			return this->internalFindChildFromPtr(out, toFind, recursive);
		}
		return false;
	}

	bool Component::existsChildFromPtr(const void* toFind, const bool recursive)
	{
		if (toFind)
		{
			MutexLocker locker(pMutex);
			return this->internalExistsChildFromPtr(toFind, recursive);
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
				for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
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
		return (uint32)pChildren.size();
	}


	SharedPtr<Component> Component::child(const uint32 indx)
	{
		MutexLocker locker(pMutex);
		return (pState != csReady || pChildren.empty() || pChildren.size() >= indx) ? SharedPtr<Component>() : pChildren[indx];
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
			this->broadcastOnBeforeDestruction();
			// We can safely unlock here all references have been destroyed
			pMutex.unlock();

			// All children will really be destroyed here
			return;
		}
		pMutex.unlock();
	}


	void Component::broadcastOnBeforeDestruction()
	{
		for (Vector::iterator i = pChildren.begin(); i != pChildren.end(); ++i)
			(*i)->onBeforeDestruction();
	}


	Component::State Component::state()
	{
		MutexLocker locker(pMutex);
		return pState;
	}


	bool Component::valid()
	{
		MutexLocker locker(pMutex);
		return (pState == csReady);
	}



} // namespace UI
} // namespace Gfx
} // namespace Yuni

