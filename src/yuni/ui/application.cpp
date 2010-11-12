
#include "application.h"
#include <cassert>

namespace Yuni
{
namespace UI
{

	// An empty string represents an invalid GUID
	const Application::GUID Application::InvalidGUID = "";


	namespace // Anonymous
	{

		IComponent::ID NextID = 0;

	} // namespace Anonymous


	IComponent::ID Application::createID() const
	{
		return NextID++;
	}


	void Application::GenerateGUID(Application::GUID& guid)
	{
		assert(guid.size() == 0 && "The GUID must be empty at this point");

		// FIXME : Use real GUID and not this stupid one (and the mutex must be removed too)
		static int I = 0;
		static Mutex mutex;

		mutex.lock();
		guid = "f81d4fae-7dec-11d0-a765-00a0c91e6bf6";
		CustomString<10, false> t;
		guid.overwriteRight((t << I++));
		mutex.unlock();
	}


	void Application::initialize()
	{
		// Prepare a new GUI for the application
		// The const_cast is quite ugly but after this point, the guid _must_ not be
		// modified
		GenerateGUID(const_cast<GUID&>(pGUID));
		onShowWindow.connect(this, &Application::showWindow);
		onHideWindow.connect(this, &Application::hideWindow);
		onCloseWindow.connect(this, &Application::closeWindow);
		onShowComponent.connect(this, &Application::showComponent);
		onHideComponent.connect(this, &Application::hideComponent);
		onUpdateComponent.connect(this, &Application::updateComponent);
		disconnectWL();
	}


	void Application::quit()
	{
		ThreadingPolicy::MutexLocker lock(*this);

		Window::Map::iterator end = pWindows.end();
		for (Window::Map::iterator it = pWindows.begin(); it != end; ++it)
		{
			it->second->close();
		}
		destroyBoundEvents();
	}


	void Application::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);

		Window::Map::iterator end = pWindows.end();
		for (Window::Map::iterator it = pWindows.begin(); it != end; ++it)
			it->second->show();
	}


	void Application::reconnectWL()
	{
		Window::Map::iterator end = pWindows.end();
		for (Window::Map::iterator it = pWindows.begin(); it != end; ++it)
		{
			reconnectOneWindowWL(it->second);
		}
	}


	void Application::reconnectOneWindowWL(Window::Ptr window)
	{
		window->onShowWindow = &onShowWindow;
		window->onHideWindow = &onHideWindow;
		window->onCloseWindow = &onCloseWindow;
		window->onShowComponent = &onShowComponent;
		window->onHideComponent = &onHideComponent;
		window->onUpdateComponent = &onUpdateComponent;
	}


	void Application::disconnectWL()
	{
		onApplicationShowWindow = nullptr;
		onApplicationHideWindow = nullptr;
		onApplicationCloseWindow = nullptr;
		onApplicationShowComponent = nullptr;
		onApplicationHideComponent = nullptr;
		onApplicationUpdateComponent = nullptr;
		// Reconnect will only propagate the null pointers to children windows
		reconnectWL();
	}



} // namespace UI
} // namespace Yuni
