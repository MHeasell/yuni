
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
		// Lock
		ThreadingPolicy::MutexLocker locker(*this);

		// There is nothing to do if the device is null
		if (newDevice == nullptr)
			return false;

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


	bool Gfx3D::resetWithFailSafeSettings(const bool fullscreenMode)
	{
		// Informations about the device
		Gfx::Device::Ptr newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);
		// The fail-safe resolution
		Device::Display::Resolution::Ptr fsRes(new Device::Display::Resolution(800, 600));
		newDevice->resolution(fsRes);

		// Apply the new settings
		return reset(newDevice);
	}


	bool Gfx3D::resetWithDefaultSettings(const bool fullscreenMode)
	{
		// Informations about the device
		Gfx::Device::Ptr newDevice(new Gfx::Device());
		newDevice->fullscreen(fullscreenMode);

		// Apply the new settings
		return reset(newDevice);
	}


} // namespace Application
} // namespace Yuni


