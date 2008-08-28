
# include <yuni/yuni.h>
# include <yuni/gfx/ui/window.h>



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	Window::Window()
		:pMutex(), pTitle(), pName(), pRefComponents()
	{}

	Window::~Window()
	{}

	
	void Window::registerComponent(Component* comPtr)
	{
		pMutex.lock();
		if (comPtr && !(comPtr->name().empty()))
			pRefComponents[comPtr->name()] = comPtr;
		pMutex.unlock();
	}

	void Window::unregisterComponent(const Component* comPtr)
	{
		pMutex.lock();
		if (comPtr && !(comPtr->name().empty()))
			pRefComponents.erase(comPtr->name());
		pMutex.unlock();
	}
	
	SharedPtr<Component> Window::findComponent(const String& comName)
	{
		MutexLocker locker(pMutex);
		return comName.empty() ? NULL : pRefComponents.value(comName, NULL);
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


