
#include "gfx3d.h"
#include "../toolbox/smartptr/sharedptr.h"
#include "../gfx/device.h"


namespace Yuni
{
namespace Application
{

	namespace
	{

		void GracefullyStopTheEngine(void)
		{
			Gfx::Engine::Instance()->release();
		}

	} // anonymous namespace


	Gfx3D::Gfx3D(int argc, char* argv[])
		:AApplication(argc, argv), Event::Receiver(), device()
	{
		Gfx::Engine::Instance()->applicationTitle("Loading");
		atexit(&GracefullyStopTheEngine);
	}


	Gfx3D::~Gfx3D()
	{
		// Ensures all notifiers are not linked with this class
		this->disconnectAllNotifiers();
	}

	

	void Gfx3D::execute()
	{
		if (!Gfx::Engine::Instance()->resetWithFailSafeSettings())
			return;

		// Event: OnPreExecute()
		if (onPreExecute())
		{
			// Run the 3D engine in an infinite loop
			Gfx::Engine::Instance()->run();
		}

		// Releasing the Engine
		Gfx::Engine::Instance()->release();
	}



} // namespace Application
} // namespace Yuni


