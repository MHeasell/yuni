
#include "desktop.h"

namespace Yuni
{
namespace UI
{


	void Desktop::close()
	{
		Application::Map::iterator end = pApps.end();
		for (Application::Map::iterator it = pApps.begin(); it != end; ++it)
		{
			it->second->close();
		}
	}



} // namespace UI
} // namespace Yuni
