#ifndef __YUNI_PRIVATE_GFX3D_ABSTRACT_H__
# define __YUNI_PRIVATE_GFX3D_ABSTRACT_H__

# include "../../yuni.h"
# include "../../gfx/device.h"
# include "../../toolbox/smartptr/sharedptr.h"
# include "../../threads/mutex.h"
# include "../../misc/event.h"



namespace Yuni
{
namespace Private
{
namespace Gfx
{



	/*!
	** \brief Base class for back-end 3D engine (abstract)
	**
	** \see class Yuni::Private::Gfx::Irrlich::Engine
	*/
	class EngineAbstract
	{
	public:
		//! \name Constructor & Destructor
		//@{

		//! Default Constructor
		EngineAbstract();

		//! Destructor
		virtual ~EngineAbstract();

		//@}


		//! \name Information about the 3D Device back-end
		//@{

		//! Name of the Gfx back-end
		virtual String name() const = 0;

		//! The FPS count
		sint32 fps() const {return pFPS;}

		//! Get if the engine is running
		bool isRunning() const {return pIsRunning;}

		//! Get if the engine is ready
		virtual bool ready() const = 0;

		//@}

		//! \name Services
		//@{

		/*!
		** \brief Initialize the 3D Device from the Gfx back-end
		**
		** If the device is already initialize, it will be released first
		**
		** \param dc Information about the device to initialize. If NULL, nothing will be done
		** \return True if the operation succeeded, False otherwise
		*/
		virtual bool initialize(SharedPtr<Yuni::Gfx::Device> dc) = 0;

		/*!
		** \brief Release the last initialized 3D Device
		**
		** If the device is not initialized, nothing will be done. This method will be
		** automatically called by the destructor.
		*/
		virtual void release() = 0;

		/*!
		** \brief Run the device
		*/
		virtual void run() = 0;

		/*!
		** \brief Wait for the engine to stop
		**
		** \internal The device will only be closed, but not destroyed. This feature is mainly
		** useful to reset on the fly the screen resolution
		*/
		virtual void waitForEngineToStop() = 0;

		//@} // Services


		//! \name Application title
		//@{
		//! Get the application title
		String applicationTitle();
		//! Set the application title
		virtual void applicationTitle(const String& t) = 0;
		//@}


	public:
		//! Event: THe FPS has changed
		Event::E1<int> onFPSChanged;

	protected:
		//! Mutex
		Mutex pMutex;
		//! FPC count
		sint32 pFPS;
		//! Get if the engine is running
		bool pIsRunning;
		//! Application title
		String pApplicationTitle;

	}; // class Abstract



} // namespace Gfx
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_GFX3D_ABSTRACT_H__
