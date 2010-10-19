
#include "application.h"

namespace Yuni
{
namespace UI
{
	namespace // Anonymous
	{

		IComponent::ID NextID = 0;

	} // namespace Anonymous


	IComponent::ID Application::createID() const
	{
		return NextID++;
	}


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
