
#include <iostream>
#include "gl.engine.h"
#include "../../../core/system/sleep.h"
#include "../../../threads.h"
#include "../../../device/display/resolution.h"

namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Gl
{

	Engine::Engine()
		:Private::Gfx::EngineAbstract(), pBackgroundColor(0, 0, 0, 0),
		pRunnable(false)
	{}

	Engine::Engine(SmartPtr<Yuni::Gfx::Device> dc)
		:Private::Gfx::EngineAbstract(), pRunnable(false)
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

		// Clear The Background Color To Black
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Enables Clearing Of The Depth Buffer
		glClearDepth(1.0);
		// The Type Of Depth Test To Do
		glDepthFunc(GL_LESS);
		// Enables Depth Testing
		glEnable(GL_DEPTH_TEST);
		// Enables Smooth Color Shading
		glShadeModel(GL_SMOOTH);

		glMatrixMode(GL_PROJECTION);
		// Reset The Projection Matrix
		glLoadIdentity();
		// Calculate The Aspect Ratio Of The Window
		Device::Display::Resolution::Ptr res = dc->resolution();
		gluPerspective(45.0f, (GLfloat)res->width() / (GLfloat)res->height(), 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);

		// Set the window caption
		this->applicationTitle(pApplicationTitle);
		pRunnable = true;
		return true;
	}



	void Engine::run()
	{
		if (!pDevice) // No device, aborting
			return;
		while (pRunnable)
			// TODO
			;
		pRunnable = false;
	}


	void Engine::release()
	{
		pRunnable = false;
		if (pDevice)
		{
			// Close the device
			waitForEngineToStop();
		}
		pDevice = NULL;
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

		if (pDevice && pIsRunning)
		{
			ThreadWaitForEngineToStop th(*this);
			th.start();
			// Let the other thread
			SleepMilliSeconds(100 /* ms */);
			th.stop(10);

			// Does not destroy the device, it will only be closed
			//pDevice->closeDevice();
		}
	}


	void Engine::applicationTitle(const String& t)
	{
		pMutex.lock();
		if (pDevice)
		{
			pApplicationTitle = t;
		}
		pMutex.unlock();
	}




} // namespace Irrlicht
} // namespace Gfx
} // namespace Private
} // namespace Yuni

