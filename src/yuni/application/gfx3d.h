#ifndef __YUNI_APPLICATION_GFX_3D_H__
# define __YUNI_APPLICATION_GFX_3D_H__

# include "application.h"
# include "../gfx/device.h"
# include "../core/event/event.h"
# include "../gfx/loop.h"
# include "../ui/desktop.h"

namespace Yuni
{
namespace Application
{


	/*!
	** \brief 3D Application
	*/
	class Gfx3D : public Application::IApplication, public IEventObserver<Gfx3D>
	{
	public:
		//! Threading policy
		typedef IEventObserver<Gfx3D>::ThreadingPolicy  ThreadingPolicy;


	public:
		//! \name Constructor & Destructor
		//@{

		/*!
		** \brief Constructor
		** \param argc The number of arguments
		** \param argv All arguments
		*/
		Gfx3D(int argc, char* argv[]);

		//! Destructor
		virtual ~Gfx3D();

		//@}

		//! \name Application title
		//@{
		//! Get the application title
		String title() const;

		//! Set the application title
		template<class StringT>
		void title(const StringT& t);
		//@}


		//! \name Events
		//@{

		/*!
		** \brief Event: Before the 3D Device is created
		*/
		virtual void onBeforeCreateDevice();

		/*!
		** \brief Event: After the 3D Device has been created
		**
		** \param bool True if the creation of the 3D device has succeeded
		*/
		virtual void onAfterCreateDevice(const bool /* success */);


		/*!
		** \brief Event: Before launching the loop
		**
		** \returns True to continue with execution, false to stop
		*/
		virtual bool onBeforeLoop();

		/*!
		** \brief What to do on execute.
		*/
		virtual void onExecute();

		//@}


		//! \name Device manipulation
		//@{
		//! Get graphics device information
		Gfx::Device::Ptr device() const;

		//! Is the device properly initialized ?
		bool isDeviceInitialized() const;

		/*!
		** \brief Reset the 3D Device
		**
		** If the 3D Device has already been initialized, it will be
		** released first.
		**
		** \param dc Informations about the device to initialize.
		** \return True if the operation succeeded, False otherwise
		*/
		bool reset(const Gfx::Device::Ptr& dc);

		/*!
		** \brief Reset the 3D Device with optimal settings
		**
		** \param fullscreenMode True to enable the fullscreen mode
		** \return True if the operation succeeded, False otherwise
		*/
		bool resetWithDefaultSettings(const bool fullscreenMode = true);

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
		//@}


	public:
		//! UI tree root
		UI::Desktop::Ptr desktop;


	private:
		//! Application title
		String pTitle;

		//! Event loop
		Gfx::Loop pLoop;

		//! Is the device properly initialized ?
		bool pDeviceIsInitialized;

	}; // class Application::Gfx3D




} // namespace Application
} // namespace Yuni

# include "gfx3d.hxx"

#endif // __YUNI_APPLICATION_GFX_3D_H__
