
#include "desktop.h"

namespace Yuni
{
namespace UI
{

	Desktop::Desktop()
	{
		// Initialize event pointers to null
		disconnectWL();
	}


	void Desktop::quit()
	{
		ThreadingPolicy::MutexLocker lock(*this);

		Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
		{
			it->second->quit();
		}
	}


	void Desktop::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);

		Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
			it->second->show();
	}


	void Desktop::disconnectWL()
	{
		onShowWindow.clear();
		onHideWindow.clear();
		onCloseWindow.clear();
		onShowComponent.clear();
		onHideComponent.clear();
		onUpdateComponent.clear();
	}


	void Desktop::reconnectWL()
	{
		Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
		{
			// Reconnect application events
			reconnectOneApplicationWL(it->second);
		}
	}


	void Desktop::reconnectOneApplicationWL(Application::Ptr app)
	{
		app->onApplicationShowWindow = &onShowWindow;
		app->onApplicationHideWindow = &onHideWindow;
		app->onApplicationCloseWindow = &onCloseWindow;
		app->onApplicationShowComponent = &onShowComponent;
		app->onApplicationHideComponent = &onHideComponent;
		app->onApplicationUpdateComponent = &onUpdateComponent;
		app->reconnect();
	}


} // namespace UI
} // namespace Yuni
