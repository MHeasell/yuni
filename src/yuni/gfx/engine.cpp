
#include "engine.h"

#ifdef YUNI_EXTERNAL_3D_IRRLICHT
#  include "../private/gfx3d/irrlicht/irr.h"
#  include "../private/gfx3d/irrlicht/irr.engine.h"
#endif

#ifdef YUNI_EXTERNAL_3D_OGRE
#  include "../private/gfx3d/ogre/ogre.h"
#  include "../private/gfx3d/ogre/ogre.engine.h"
#endif


namespace Yuni
{
namespace Gfx
{
	namespace
	{

		/*!
		* \brief The external 3D engine
		*/
		# ifdef YUNI_EXTERNAL_3D_IRRLICHT
		Private::Gfx::Irrlicht::Engine external3DEngine;
		# else
		# ifdef YUNI_EXTERNAL_3D_OGRE
		Private::Gfx::Ogre::Engine external3DEngine;
		# else
		#	error "The external 3D engine is not defined"
		# endif
		# endif

		Engine globalEngine;

	} // anonymous namespace



	Engine* Engine::Instance()
	{
		return &globalEngine;
	}


	Engine::Engine()
		:pDeviceIsInitialized(false)
	{
		// Redirect all events
		onFPSChanged.assign(&external3DEngine.onFPSChanged);
	}


	Engine::~Engine()
	{
		// Disconnect all connected events
		onFPSChanged.disconnectAll();
		this->release();
	}



	String Engine::name()
	{
		MutexLocker locker(pMutex);
		return external3DEngine.name();
	}



	bool Engine::reset(const SmartPtr<Device>& dc)
	{
		// Lock
		MutexLocker locker(pMutex);

		// Ensure that a device is not already initialized
		external3DEngine.waitForEngineToStop();

		// There is nothing to do if the device is null
		if (NULL != dc)
		{
			// Getting a reference to the information about the Device
			pDevice = dc;
			// The settings must be valid
			// e.g. the resolution must be a valid resolution
			pDevice->ensuresSettingsAreValid();

			// Ask to the back-end engine to initialize itself
			pDeviceIsInitialized = external3DEngine.initialize(pDevice);

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
			external3DEngine.run();
			return;
		}
		pMutex.unlock();
	}


	void Engine::release()
	{
		pMutex.lock();
		if (pDeviceIsInitialized)
		{
			pMutex.unlock();
			// Ensure that a device is not already initialized
			external3DEngine.waitForEngineToStop();
			// Releasing...
			external3DEngine.release();

			pMutex.lock();
			pDeviceIsInitialized = false;
		}
		pMutex.unlock();
	}


	void Engine::applicationTitle(const String& t)
	{
		external3DEngine.applicationTitle(t);
	}


	String Engine::applicationTitle()
	{
		return (dynamic_cast<Private::Gfx::EngineAbstract*>(&external3DEngine))->applicationTitle();
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

