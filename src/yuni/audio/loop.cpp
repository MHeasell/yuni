#include "loop.h"
#include "manager.h"

namespace Yuni
{
namespace Audio
{

	bool Loop::onLoop()
	{
		Manager::Instance().updateWL();
		return true;
	}



} // namespace Audio
} // namespace Yuni
