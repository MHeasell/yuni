
#include "application.h"

namespace Yuni
{
namespace UI
{


	void Application::close()
	{
		Window::Vector::iterator end = pWindows.end();
		for (Window::Vector::iterator it = pWindows.begin(); it != end; ++it)
		{
			(*it)->close();
		}
	}



} // namespace UI
} // namespace Yuni
