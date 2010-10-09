
#include "gfx3d.h"

namespace Yuni
{
namespace Application
{


	void Gfx3D::onExecute()
	{
		// Event: OnBeforeCreateDevice()
		onBeforeCreateDevice();
		bool deviceOK = resetWithDefaultSettings();
		if (!deviceOK)
			deviceOK = resetWithFailSafeSettings();
		// Event: OnAfterCreateDevice()
		onAfterCreateDevice(deviceOK);
		if (!deviceOK)
			return;

		// Event: OnBeforeLoop()
		if (onBeforeLoop())
		{
			// Run the 3D engine in an infinite loop
			pLoop.start();
		}

		// Releasing the Engine
		pLoop.stop();
	}


	bool Gfx3D::reset(const Gfx::Device::Ptr& newDevice)
	{
		// There is nothing to do if the device is null
		if (!newDevice)
			return false;

		// Lock
		ThreadingPolicy::MutexLocker locker(*this);

		// Getting a reference to the information about the Device
		pLoop.device = newDevice;

		// The settings must be valid
		// e.g. the resolution must be a valid resolution
		pLoop.device->ensureSettingsAreValid();

		pDeviceIsInitialized = true;

		// Lock further modifications to the informations about the device
		pLoop.device->lock();

		return pDeviceIsInitialized;
	}


	bool Gfx3D::resetWithFailSafeSettings(bool fullscreenMode)
	{
		// Informations about the device
		Gfx::Device* newDevice = new Gfx::Device();
		newDevice->fullscreen(fullscreenMode);
		// The fail-safe resolution
		Device::Display::Resolution* defaultResolution = new Device::Display::Resolution(800, 600);
		newDevice->resolution(defaultResolution);

		// Apply the new settings
		return reset(newDevice);
	}


	bool Gfx3D::resetWithDefaultSettings(bool fullscreenMode)
	{
		// Informations about the device
		Gfx::Device* newDevice = new Gfx::Device();
		newDevice->fullscreen(fullscreenMode);

		// Apply the new settings
		return reset(newDevice);
	}




} // namespace Application
} // namespace Yuni

