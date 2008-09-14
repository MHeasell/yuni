
#include "abstract.h"


namespace Yuni
{
namespace Private
{
namespace Gfx
{

	EngineAbstract::EngineAbstract()
		:pFPS(0), pIsRunning(false), pApplicationTitle("Loading")
	{}

	EngineAbstract::~EngineAbstract()
	{
		onFPSChanged.disconnectAll();
	}


	String EngineAbstract::applicationTitle()
	{
		MutexLocker locker(pMutex);
		return pApplicationTitle;
	}



} // namespace Gfx
} // namespace Private
} // namespace Yuni

