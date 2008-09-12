
#include "gfx3d.h"
#include "../misc/sharedptr.h"
#include "../gfx/device.h"
#include "../gfx/engine.h"


namespace Yuni
{
namespace Application
{

	Gfx3D::Gfx3D(int argc, char* argv[])
		:Abstract(argc, argv), device()
	{}

	Gfx3D::~Gfx3D()
	{}

	
	void Gfx3D::initializeEngine()
	{
		// Informations about the device
		SharedPtr<Gfx::Device> device(new Gfx::Device());
		// Initializing the Engine
		Gfx::Engine::Instance()->initialize(device);
	}

	void Gfx3D::execute()
	{
		// Initialize the engine
		this->initializeEngine();

		// Event: OnPreExecute()
		if (onPreExecute())
		{
		}

		// Releasing the Engine
		Gfx::Engine::Instance()->release();
	}

} // namespace Application
} // namespace Yuni


