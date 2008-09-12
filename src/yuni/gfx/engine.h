#ifndef __YUNI_GFX_ENGINE_H__
# define __YUNI_GFX_ENGINE_H__

# include "device.h"
# include "../misc/sharedptr.h"



namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief
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
		** \brief Destructor
		*/
		~Engine();

		/*!
		** \brief Get the name of the external 3D engine
		*/
		String name() const;

		/*!
		** \brief Initialize the 3D device
		**
		** If the 3D Device has already been initialized, it will be
		** released first.
		**
		** \param dc Informations about the device to initialize.
		** \return True if the operation succeeded, False otherwise
		*/
		bool initialize(const SharedPtr<Device>& dc);

		/*!
		** \brief Release the 3D engine
		*/
		void release();

		/*!
		** \brief Get informations about the device currently being used
		*/
		SharedPtr<Device> device() const {return pDevice;}

	private:
		/*!
		** \brief Private constructor
		*/
		Engine();

	private:
		bool pDeviceIsInitialized;
		//! Information about the device
		SharedPtr<Device> pDevice;

	}; // class Engine



} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_ENGINE_H__
