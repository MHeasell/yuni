#ifndef __YUNI_UI_QUEUESERVICE_H__
# define __YUNI_UI_QUEUESERVICE_H__

# include "application.h"
# include "../gfx/device.h"
# include "../core/event/event.h"
# include "../ui/loop.h"
# include "../ui/desktop.h"



namespace Yuni
{
namespace UI
{

	/*!
	** \brief UI queue service
	*/
	class QueueService : public IEventObserver<QueueService>
	{
	public:
		//! Threading policy
		typedef IEventObserver<QueueService>::ThreadingPolicy  ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		QueueService();

		//! Destructor
		virtual ~QueueService();
		//@}


	public:
		/*!
		** \brief Start the audio service
		*/
		bool start();

		/*!
		** \brief Stop the audio service
		*/
		void stop();


		//! \name Events
		//@{
		/*!
		** \brief Event: Before the 3D Device is created
		*/
		Event<void (void)> onBeforeCreateDevice;

		/*!
		** \brief Event: After the 3D Device has been created
		**
		** \param bool True if the creation of the 3D device has succeeded
		*/
		Event<void (bool /* success */)> onAfterCreateDevice;

		/*!
		** \brief Event: Before launching the loop
		**
		** \returns True to continue with execution, false to stop
		*/
		Event<bool (void)> onBeforeLoop;
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
		bool resetWithDefaultSettings(bool fullscreenMode = true);

		/*!
		** \brief Reset the 3D Device with safe settings
		**
		** \param fullscreenMode True to enable the fullscreen mode
		** \return True if the operation succeeded, False otherwise
		*/
		bool resetWithFailSafeSettings(bool fullscreenMode = false);

		/*!
		** \brief Toggle the fullscreen mode
		** \return The current status of the fullscreen mode
		*/
		bool toggleFullscreen();
		//@}


	public:
		//! UI tree root
		Desktop::Ptr desktop;


	private:
		//! Event loop
		Loop pLoop;

		//! Is the device properly initialized ?
		bool pDeviceIsInitialized;


	}; // class QueueService





} // namespace UI
} // namespace Yuni

# include "queueservice.hxx"

#endif // __YUNI_UI_QUEUESERVICE_H__
