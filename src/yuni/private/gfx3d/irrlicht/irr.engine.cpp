
#include "irr.h"
#include "irr.engine.h"
#include "../../../toolbox/system/sleep.h"
#include "../../../threads.h"
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
		:Private::Gfx::EngineAbstract(), pIrrDevice(NULL), pBackgroundColor(0, 0, 0, 0),
		pRunnable(false)
	{}

	Engine::Engine(SmartPtr<Yuni::Gfx::Device> dc)
		:Private::Gfx::EngineAbstract(), pIrrDevice(NULL)
	{
		this->initialize(dc);
	}


	Engine::~Engine()
	{
		pRunnable = false;
		onFPSChanged.disconnectAll();
		release();
	}



	bool Engine::initialize(SmartPtr<Yuni::Gfx::Device> dc)
	{
		// We keep a reference to the yuni device
		if (NULL == dc)
			return false;

		// Ensure that a device is not already initialized
		release();
		// Getting a reference to the information about the Device
		pDevice = dc;
		// Create the Irrlicht device
		pIrrDevice = irr::createDevice(YuniDeviceToIrrDevice(dc->type()),
									   //irr::core::dimension2d<irr::s32>(pDevice->resolution()->width(), pDevice->resolution()->height()),
									   irr::core::dimension2d<irr::s32>(800, 600),
									   (int) pDevice->resolution()->bitPerPixel(),
									   pDevice->fullscreen(), pDevice->stencilbuffer(), pDevice->vsync(), NULL);

		if (pIrrDevice)
		{
			// Set the window caption
			this->applicationTitle(pApplicationTitle);
			pRunnable = true;
			return true;
		}
		return false;
	}



	void Engine::run()
	{
		if (!pIrrDevice) // No device, aborting
			return;

		// The Irrlicht Video driver
		pIrrVideoDriver  = pIrrDevice->getVideoDriver();
		// The Irrlicht scene manager
		pIrrSceneManager = pIrrDevice->getSceneManager();
		// Those vars must be valid
		if (!pIrrVideoDriver || !pIrrSceneManager) // It seems that is not the case
			return;

		// Reduces the scheduling priority for some processes
		// . When the FPS counter changes, it broadcasts an event. However, this information
		//   is not critical and the scheduling priority should be decreased
		// . It is the same to check if the window is active
		int limitCPUConsuming = 1;
		// Indicates that the engine is running
		pIsRunning = true;
		// Ready to loop
		pRunnable = true;

		while (pRunnable && pIrrDevice->run()) // Cycle
		{
			// Begin the entire scene
			pIrrVideoDriver->beginScene(true, true, pBackgroundColor);
			// Draw all 3D objects
			pIrrSceneManager->drawAll();
			// End
			pIrrVideoDriver->endScene();

			--limitCPUConsuming;
			if (0 == limitCPUConsuming)
			{
				// Frames per second
				int currentFPS = pIrrVideoDriver->getFPS();
				if (currentFPS != pFPS)
				{
					pFPS = currentFPS;
					// Call event onFPSChanged here
					this->onFPSChanged(pFPS);
				}

				// When the window is inactive, there is no need for full-speed
				if (!pIrrDevice->isWindowActive())
				{
					Yuni::SleepMilliSeconds(30 /*ms*/);
				}

				// Next in 10 cycles
				limitCPUConsuming = 10; 
			}
		}

		// Resetting vars
		pIsRunning = false;
		pIrrVideoDriver = NULL;
		pIrrSceneManager = NULL;
	}


	void Engine::release()	
	{
		pRunnable = false;
		if (pIrrDevice)
		{
			// Close the device
			waitForEngineToStop();
			// Destroy the Irrlicht device
			if (pIrrDevice) // double check
				pIrrDevice->drop();
		}
		pIrrSceneManager = NULL;
		pIrrVideoDriver = NULL;
		pIrrDevice = NULL;
	}



	/*!
	 * \todo Must be removed. Created for debug purposes
	 */
	class ThreadWaitForEngineToStop : public Yuni::Threads::AThread
	{
	public:
		ThreadWaitForEngineToStop(Yuni::Private::Gfx::EngineAbstract& engineToWait)
			:Yuni::Threads::AThread(), pEngineToWait(engineToWait)
		{}

		~ThreadWaitForEngineToStop() {stop();}

		virtual void onExecute()
		{
			while (pEngineToWait.isRunning())
			{
				//suspend(1000 /* ms */);
				SleepMilliSeconds(1000);
				std::cout << "Wait...\n";
			}
		}

	private:
		Yuni::Private::Gfx::EngineAbstract& pEngineToWait;
	};



	void Engine::waitForEngineToStop()
	{
		// We should stop as soon as possible
		pRunnable = false;

		if (pIrrDevice && pIsRunning)
		{
			ThreadWaitForEngineToStop th(*this);
			th.start();
			// Let the other thread
			SleepMilliSeconds(100 /* ms */);
			th.stop(10);

			// Does not destroy the device, it will only be closed
			pIrrDevice->closeDevice();
		}
	}


	void Engine::applicationTitle(const String& t)
	{
		pMutex.lock();
		if (pIrrDevice)
		{
			pApplicationTitle = t;
			// Convertion to wchar_t
			const irr::core::stringw twchar(t.c_str());
			pIrrDevice->setWindowCaption(twchar.c_str());
		}
		pMutex.unlock();
	}




} // namespace Irrlicht
} // namespace Gfx
} // namespace Private
} // namespace Yuni

