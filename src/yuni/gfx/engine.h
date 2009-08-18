#ifndef __YUNI_GFX_ENGINE_H__
# define __YUNI_GFX_ENGINE_H__

# include "../yuni.h"
# include "device.h"
# include "../core/smartptr/smartptr.h"
# include "../core/event/event.proxy.h"
# include "../threads/mutex.h"
# include "../gfx/window/factory.h"
# include "../gfx/render/renderer.h"

namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief The graphics engine
	** \ingroup Gfx
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
		** \brief Get informations about the device currently being used
		*/
		SmartPtr<Device> device() const {return pDevice;}

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
		bool reset(const Device::Ptr& dc);

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

		//! \name Scene
		//@{
		//! Get the main scene
		Scene& scene() { return pMainScene; }
		//@}

	public:
		//! Event: The FPS has changed
		Event::E1<void, unsigned int> onFPSChanged;

	private:
		//! Mutex
		Mutex pMutex;
		//! If the device is initialized
		bool pDeviceIsInitialized;
		//! Information about the device
		Device::Ptr pDevice;
		//! Application title
		String pTitle;
		//! Main window
		Window::AWindow* pMainWindow;
		//! Main renderer
		Render::ARenderer* pRenderer;
		//! Main scene
		Scene pMainScene;

	}; // class Engine



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_ENGINE_H__
