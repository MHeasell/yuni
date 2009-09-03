
#include "engine.h"

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
		onFPSChanged.clear();
		this->release();
	}


	bool Engine::reset(const SmartPtr<Device>& dc)
	{
		// Lock
		ThreadingPolicy::MutexLocker locker(*this);

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


	bool Engine::isDeviceInitialized() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pDeviceIsInitialized;
	}


	void Engine::run()
	{
		if (!isDeviceInitialized())
			return;

		// Window creation and API init
		pMainWindow = Window::Create(applicationTitle(), pDevice);

		// The initialization has failed
		if (!pMainWindow)
			return;

		pMainWindow->verticalSync(false);
		onFPSChanged.connect(pMainWindow, &Window::AWindow::onFPSChanged);

		unsigned int lastFPS = 0;
		pRenderer = pMainWindow->renderer();

		// Main loop
		while (!pMainWindow->closing())
		{
			// Manage events on the window
			pMainWindow->pollEvents();

			// Render the frame
			pRenderer->drawFrame(*Scene::Instance());
			// FPS
			if (lastFPS != pRenderer->instantFPS())
			{
				// The FPS has changed, broadcasting the news
				lastFPS = pRenderer->instantFPS();
				onFPSChanged(lastFPS);
			}

			// Push the backbuffer to screen
			pMainWindow->onBlitWL();
		}
		pMainWindow->close();
		delete pMainWindow;
		pMainWindow = NULL;
		pRenderer = NULL;
	}


	void Engine::release()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pDeviceIsInitialized = false;
	}


	void Engine::applicationTitle(const String& t)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pTitle = t;
		if (NULL != pMainWindow)
			pMainWindow->title(pTitle);
	}


	String Engine::applicationTitle() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pTitle;
	}


	bool Engine::toggleFullscreen()
	{
		ThreadingPolicy::MutexLocker locker(*this);
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
