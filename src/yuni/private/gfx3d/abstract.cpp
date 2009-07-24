
#include "abstract.h"


namespace Yuni
{
namespace Private
{
namespace GfxImpl
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



} // namespace GfxImpl
} // namespace Private
} // namespace Yuni

