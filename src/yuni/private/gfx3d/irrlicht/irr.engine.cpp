
#include "irr.h"
#include "irr.engine.h"
#include "../../../system/sleep.h"
#include <iostream>



namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Irrlicht
{


	irr::video::E_DRIVER_TYPE Engine::YuniDeviceToIrrDevice(const Yuni::Gfx::Device::Type& t)
	{
		switch (t)
		{
			// case Yuni::Gfx::Device::ygdtNull     : { return irr::video::EDT_NULL; }
			# ifndef YUNI_OS_DARWIN
			case Yuni::Gfx::Device::ygdtSoftware : { return irr::video::EDT_BURNINGSVIDEO; }
			# endif
			case Yuni::Gfx::Device::ygdtOpenGL   : { return irr::video::EDT_OPENGL; }
			# ifdef YUNI_OS_WINDOWS
			case Yuni::Gfx::Device::ygdtDirectX9 : { return irr::video::EDT_DIRECT3D9; }
			case Yuni::Gfx::Device::ygdtDirectX8 : { return irr::video::EDT_DIRECT3D8; }
			# endif
			// The defaut renderer should be OpenGL
			default : { return irr::video::EDT_OPENGL; }
		}
		return irr::video::EDT_OPENGL;
	}


	Engine::Engine()
		:Private::Gfx::Abstract(), pIrrDevice(NULL)
	{}

	Engine::Engine(SharedPtr<Yuni::Gfx::Device> dc)
		:Private::Gfx::Abstract(), pIrrDevice(NULL)
	{
		this->initialize(dc);
	}


	Engine::~Engine()
	{
		release();
	}


	
	bool Engine::initialize(SharedPtr<Yuni::Gfx::Device> dc)
	{
		// We keep a reference to the yuni device
		if (dc.null())
			return false;

		// Ensure that a device is not already initialized
		release();

		// Getting a reference to the information about the Device
		pDevice = dc;

		// Create the Irrlicht device
		std::cout << "[yuni] " << pDevice << std::endl;
		pIrrDevice = irr::createDevice(YuniDeviceToIrrDevice(dc->type()),
				irr::core::dimension2d<irr::s32>(pDevice->resolution()->width(), pDevice->resolution()->height()),
				(int) pDevice->resolution()->bitPerPixel(),
				pDevice->fullscreen(), pDevice->stencilbuffer(), pDevice->vsync(), NULL);

		if (pIrrDevice)
		{
			// The Irrlicht Video driver
			pIrrVideoDriver  = pIrrDevice->getVideoDriver();
			// The Irrlicht scene manager
			pIrrSceneManager = pIrrDevice->getSceneManager();

			if (pIrrVideoDriver && pIrrSceneManager) // Ok, all pointers seem valid
				return true;

			// Error, releasing the resources
			pIrrDevice->drop();
		}

		// Error
		pIrrDevice = NULL;
		pIrrVideoDriver = NULL;
		pIrrSceneManager = NULL;

		return false;
	}


	void Engine::run()
	{
		if (!pIrrDevice)
			return;

		// The default background color
		const irr::video::SColor backgroundColor(255, 100, 101,  140);

		while (pIrrDevice->run())
		{
			// Begin the entire scene
			pIrrVideoDriver->beginScene(true, true, backgroundColor);
			// Draw all 3D objects
			pIrrSceneManager->drawAll();
			// End
			pIrrVideoDriver->endScene();

			// Frame per second
			int currentFPS = pIrrVideoDriver->getFPS();
			if (currentFPS)
			{
				pFPS = currentFPS;
				// Call event onFPSChanged here
			}

			// When the window is inactive, there is no need for full-speed
			if (!pIrrDevice->isWindowActive())
				Yuni::Sleep(10 /*ms*/);
		}
	}


	void Engine::release()
	{
		if (pIrrDevice)
		{
			pIrrDevice->drop();
			pIrrSceneManager = NULL;
			pIrrVideoDriver = NULL;
			pIrrDevice = NULL;
		}
	}


} // namespace Irrlicht
} // namespace Gfx
} // namespace Private
} // namespace Yuni


