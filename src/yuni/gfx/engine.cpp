
#include "engine.h"
#include "api/gl.h"
#include "render/opengl.h"

namespace Yuni
{
namespace Gfx
{
	namespace
	{

		Engine globalEngine;

	} // anonymous namespace



	Engine* Engine::Instance()
	{
		return &globalEngine;
	}


	Engine::Engine()
		:pDeviceIsInitialized(false), pMainWindow(NULL), pRenderer(NULL)
	{
	}


	Engine::~Engine()
	{
		onFPSChanged.disconnectAll();
		this->release();
	}


	bool Engine::reset(const SmartPtr<Device>& dc)
	{
		// Lock
		MutexLocker locker(pMutex);

		// There is nothing to do if the device is null
		if (NULL != dc)
		{
			// Getting a reference to the information about the Device
			pDevice = dc;
			// The settings must be valid
			// e.g. the resolution must be a valid resolution
			pDevice->ensuresSettingsAreValid();

			pDeviceIsInitialized = true;

			// Lock further modifications to the informations about the device
			pDevice->lock();
		}
		return pDeviceIsInitialized;
	}



	bool Engine::resetWithFailSafeSettings(const bool fullscreenMode)
	{
		// Informations about the device
		SmartPtr<Gfx::Device> newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);
		// The fail-safe resolution
		SmartPtr<Yuni::Device::Display::Resolution> fsRes(new Yuni::Device::Display::Resolution(800, 600));
		newDevice->resolution(fsRes);

		// Apply the new settings
		return this->reset(newDevice);
	}



	bool Engine::resetWithRecommendedSettings(const bool fullscreenMode)
	{
		// Informations about the device
		SmartPtr<Gfx::Device> newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);

		// Apply the new settings
		return this->reset(newDevice);
	}


	void Engine::run()
	{
		pMutex.lock();
		if (pDeviceIsInitialized)
		{
			pMutex.unlock();

			// Window creation and API init
# if defined(YUNI_WINDOWSYSTEM_MSW) && defined(YUNI_USE_DIRECTX)
			pMainWindow = Window::Factory::CreateDX9Window(applicationTitle(), pDevice->resolution()->width(),
				pDevice->resolution()->height(), pDevice->resolution()->bitPerPixel(), pDevice->fullscreen());
# else
			pMainWindow = Window::Factory::CreateGLWindow(applicationTitle(), pDevice->resolution()->width(),
				pDevice->resolution()->height(), pDevice->resolution()->bitPerPixel(), pDevice->fullscreen());
# endif
			
			pMainWindow->verticalSync(false);
			onFPSChanged.connect(pMainWindow, &Window::AWindow::onFPSChanged);

			static unsigned int lastFPS = 0;
			pRenderer = new Render::OpenGL();

			// Main loop
			while (!pMainWindow->closing())
			{
				// Manage events on the window
				pMainWindow->pollEvents();

				pRenderer->drawFrame(*Scene::Instance());
				if (lastFPS != pRenderer->instantFPS())
				{
					lastFPS = pRenderer->instantFPS();
					onFPSChanged(lastFPS);
				}

				// Push the backbuffer to screen
				pMainWindow->blit();
			}
			pMainWindow->close();
			delete pMainWindow;
			pMainWindow = NULL;
			delete pRenderer;
			pRenderer = NULL;
		}
		pMutex.unlock();
	}


	void Engine::release()
	{
		pMutex.lock();
		if (pDeviceIsInitialized)
		{
			pDeviceIsInitialized = false;
		}
		pMutex.unlock();
	}


	void Engine::applicationTitle(const String& t)
	{
		pTitle = t;
		if (NULL != pMainWindow)
			pMainWindow->title(pTitle);
	}


	String Engine::applicationTitle()
	{
		return pTitle;
	}


	bool Engine::toggleFullscreen()
	{
		// Lock
		MutexLocker locker(pMutex);
		// Toggle the flag for the fullscreen mode
		const bool f = pDevice->toggleFullscreen();
		// Reset the device
		// TODO Find a better way to toggle the fullscreen mode
		this->reset(pDevice);
		// Return the current status for the fullscreen mode
		return f;
	}



} // namespace Gfx
} // namespace Yuni

