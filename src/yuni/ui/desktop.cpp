
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




} // namespace UI
} // namespace Yuni
