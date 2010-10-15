
#include "desktop.h"

namespace Yuni
{
namespace UI
{


	void Desktop::quit()
	{
		Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
		{
			it->second->quit();
		}
	}



} // namespace UI
} // namespace Yuni
