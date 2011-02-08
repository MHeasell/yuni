
#include "desktop.h"

namespace Yuni
{
namespace UI
{

	Desktop::Desktop()
	{
	}


	void Desktop::quit()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		const Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
			it->second->quit();
	}


	void Desktop::show()
	{
		ThreadingPolicy::MutexLocker lock(*this);
		const Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
			it->second->show();
	}


	void Desktop::disconnectWL()
	{
		pLocalEvents.clear();
	}


	void Desktop::reconnectWL()
	{
		const Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
			reconnectOneApplicationWL(it->second);
	}


	void Desktop::reconnectOneApplicationWL(const Application::Ptr& application)
	{
		application->reconnectLocalEvents.clear();
		application->reconnectLocalEvents.connect(this, &Desktop::reconnectLocalEvents);
		application->reconnect();
	}


	void Desktop::reconnectLocalEvents(LocalUIEvents& events)
	{
		events = pLocalEvents;
	}


} // namespace UI
} // namespace Yuni
