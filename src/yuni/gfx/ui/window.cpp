
# include <yuni/yuni.h>
# include <yuni/gfx/ui/window.h>



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	Window::Window()
		:pMutex(), pTitle(), pName(), pAllComponents(), pRefComponents()
	{}

	Window::~Window()
	{
		clear();
	}



	void Window::clear()
	{
		pMutex.lock();
		pRefComponents.clear();
		pAllComponents.clear();
		pMutex.unlock();
	}


	void Window::internalRegisterComponent(Component* c)
	{
		if (c)
		{
			// Add the component to the list
			pAllComponent.push_back(SharedPtr<Component>(c));
		}
	}

	void Window::internalReRegisterComName(Component* c, const String& oldName, const String& newName)
	{
		if (!c)
			return;
		pMutex.lock();
		// We have to find the existing shared pointer to keep a valid the ref counting
		SharedPtr<Component> s (this->internalFindComponent(c));
		// Remove the previous association between the name and the component
		if (!oldName.empty())
			pRefComponents.erase(comName);
		// Set the association between the name and the component
		if (!s.null() && !newName.empty()) 
			pRefComponents[newName] = s;
		// unlcok
		pMutex.unlock();
	}

	
	SharedPtr<Component> Window::find(const String& comName)
	{
		MutexLocker locker(pMutex);
		return internalFindComponent(comName);
	}
 
	SharedPtr<Component> Window::internalFindComponent(const String& comName)
	{
		if (comName.empty()) // No component can match an empty name
			return SharedPtr<Component>();
		ComponentsByName::const_iterator it = pRefComponents.find(comName);
		return  (pRefComponents.end() == it) ? SharedPtr<Component>() : SharedPtr<Component>(it->second);
	}
 

	SharedPtr<Component> Window::find(Component* comObj)
	{
		MutexLocker locker(pMutex);
		return internalFindComponent(comObj);
	}
	
	SharedPtr<Component> Window::internalFindComponent(Component* comObj)
	{
		if (comObj)
		{
			for (Component::List::iterator i = pAllComponents.begin(); i != pAllComponents.end(); ++i)
			{
				if (i->get() == comObj)
					return SharedPtr<Component>(*i);
			}
		}
		return SharedPtr<Component>();
	}
 


	void Window::remove(const String& comName)
	{
		if (!name.empty())
		{
			pMutex.lock();
			this->internalRemove(internalFindComponent(comName));
			pMutex.unlock();
		}
	}

	void Window::remove(SharedPtr<Component> c)
	{
		pMutex.lock();
		this->internalRemove(c);
		pMutex.unlock();
	}


	void Window::internalRemove(SharedPtr<Component>& c)
	{
		if (c.null()) // no pointer, nothing to do, aborting
			return;

		// Ask to delete all its children
		c->items.clear();

		// Remove the association between its name and the component itself
		pRefComponents.erase(c->name());

		// Remove the association in the list of all components
		for (Component::List::iterator i = pAllComponents.begin(); i != pAllComponents.end(); ++i)
		{
			if (i->get() == comObj)
			{
				pAllComponents.erase(i);
				break;
			}
		}
	}



	void Window::name(const String& s)
	{
		pMutex.lock();
		pName = s;
		pMutex.unlock();
	}

	void Window::title(const String& s)
	{
		pMutex.lock();
		pTitle = s;
		pMutex.unlock();
	}

	String Window::title()
	{
		MutexLocker locker(pMutex);
		return pTitle;
	}

	String Window::name()
	{
		MutexLocker locker(pMutex);
		return pName;
	}



} // namespace UI
} // namespace Gfx
} // namespace Yuni

