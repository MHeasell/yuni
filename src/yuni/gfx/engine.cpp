
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
		: pDeviceIsInitialized(false), pUI(NULL)
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
		UI::Window::Ptr newWindow(new UI::Window("Test"));
		Gfx::Window::IWindow::Ptr mainWindow = Window::Create(newWindow, pDevice);

		// The initialization has failed
		if (!mainWindow)
			return;

		//pMainWindow->verticalSync(false);
		onFPSChanged.connect(mainWindow.pointer(), &Window::IWindow::onFPSChanged);

		//unsigned int lastFPS = 0;

		// Main loop
		while (!mainWindow->closing())
		{
			// Manage events on the window
			mainWindow->pollEvents();

			// Render the frame
			mainWindow->refresh();

			// FPS
// 			if (lastFPS != pMainSurface->instantFPS())
// 			{
// 				// The FPS has changed, broadcasting the news
// 				lastFPS = pMainSurface->instantFPS();
// 				onFPSChanged(lastFPS);
// 			}

			// Push the backbuffer to screen
			mainWindow->blitWL();
		}
		mainWindow->close();
		if (pUI)
		{
			pUI->close();
			pUI = NULL;
		}
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
	}


	String Engine::applicationTitle() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pTitle;
	}


	UI::Desktop::Ptr Engine::desktop()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pUI;
	}


	void Engine::desktop(UI::Desktop::Ptr& ui)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (pUI)
			pUI->close();
		pUI = ui;
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
