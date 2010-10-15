
#include "application.h"

namespace Yuni
{
namespace UI
{


	void Application::quit()
	{
		Window::Map::iterator end = pWindows.end();
		for (Window::Map::iterator it = pWindows.begin(); it != end; ++it)
		{
			it->second->close();
		}
	}



} // namespace UI
} // namespace Yuni
