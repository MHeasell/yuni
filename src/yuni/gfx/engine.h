#ifndef __YUNI_GFX_ENGINE_H__
# define __YUNI_GFX_ENGINE_H__

# include "device.h"
# include "../misc/sharedptr.h"
# include "../threads/mutex.h"
# include "../misc/event.proxy.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief The graphics engine
	**
	** Singleton class that manages the graphical display,
	** and the various features that go with it.
	*/
	class Engine
	{
	public:
		/*!
		** \brief Get the global instance of the engine
		*/
		static Engine* Instance();

	public:
		/*!
		** \brief Private constructor
		*/
		Engine();
		/*!
		** \brief Destructor
		*/
		~Engine();


		//! \name Information about the 3D Device
		//@{

		/*!
		** \brief Get the name of the external 3D engine
		*/
		String name();

		/*!
		** \brief Get informations about the device currently being used
		*/
		SharedPtr<Device> device() const {return pDevice;}

		//@}

		/*!
		** \brief Reset the 3D Device
		**
		** If the 3D Device has already been initialized, it will be
		** released first.
		**
		** \param dc Informations about the device to initialize.
		** \return True if the operation succeeded, False otherwise
		*/
		bool reset(const SharedPtr<Device>& dc);

		/*!
		** \brief Reset the 3D Device with optimal settings
		**
		** \param fullscreenMode True to enable the fullscreen mode
		** \return True if the operation succeeded, False otherwise
		*/
		bool resetWithRecommendedSettings(const bool fullscreenMode = true);

		/*!
		** \brief Reset the 3D Device with safe settings
		**
		** \param fullscreenMode True to enable the fullscreen mode
		** \return True if the operation succeeded, False otherwise
		*/
		bool resetWithFailSafeSettings(const bool fullscreenMode = false);

		/*!
		** \brief Toggle the fullscreen mode
		** \return The current status of the fullscreen mode
		*/
		bool toggleFullscreen();

		/*!
		** \brief Run the 3D Engine in an infinite loop
		*/
		void run();

		/*!
		** \brief Release the 3D engine
		*/
		void release();

		//! \name Application title
		//@{
		//! Get the application title
		String applicationTitle();
		//! Set the application title
		void applicationTitle(const String& t);
		//@}


	public:
		//! Event: THe FPS has changed
		Event::Proxy::P1<int> onFPSChanged;

	private:

	private:
		//! Mutex
		Mutex pMutex;
		//! If the device is initialized
		bool pDeviceIsInitialized;
		//! Information about the device
		SharedPtr<Device> pDevice;

	}; // class Engine



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_ENGINE_H__
