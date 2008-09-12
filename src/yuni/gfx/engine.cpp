
#include "engine.h"

#ifdef YUNI_EXTERNAL_3D_IRRLICHT
#  include "../private/gfx3d/irrlicht/irr.h"
#  include "../private/gfx3d/irrlicht/irr.engine.h"
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
		#	error "The external 3D engine is not defined"
		# endif

	} // anonymous namespace



	Engine* Engine::Instance()
	{
		static Engine eng;
		return &eng;
	}


	Engine::Engine()
		:pDeviceIsInitialized(false)
	{}


	Engine::~Engine()
	{
		release();
	}


	String Engine::name() const
	{
		return external3DEngine.name();
	}


	bool Engine::initialize(const SharedPtr<Device>& dc)
	{
		// Ensure that a device is not already initialized
		release();

		if (dc.valid())
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


	void Engine::release()
	{
		if (pDeviceIsInitialized)
		{
			external3DEngine.release();
			pDeviceIsInitialized = false;
		}
	}



} // namespace Gfx
} // namespace Yuni

