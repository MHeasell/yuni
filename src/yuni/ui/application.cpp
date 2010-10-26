
#include "application.h"
#include <cassert>

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
		pDesktop = nullptr;
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
