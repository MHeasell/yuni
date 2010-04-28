#include "loop.h"
#include "manager.h"

namespace Yuni
{
namespace Audio
{

	Loop::Loop(Manager* audioManager)
		:pManager(audioManager)
	{}


	bool Loop::onLoop()
	{
		if (!pManager)
			return false;
		pManager->updateDispatched();
		return true;
	}



} // namespace Audio
} // namespace Yuni
