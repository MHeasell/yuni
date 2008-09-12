#ifndef __YUNI_PRIVATE_GFX3D_ABSTRACT_H__
# define __YUNI_PRIVATE_GFX3D_ABSTRACT_H__

# include "../../yuni.h"
# include "../../gfx/device.h"
# include "../../sharedptr.h"


namespace Yuni
{
namespace Private
{
namespace Gfx
{

	class Abstract
	{
	public:
		//! \name Constructor & Destructor
		//@{

		/*!
		** \brief Default Constructor
		*/
		Abstract():pFPS(0) {}
		/*!
		** \brief Destructor
		*/
		virtual ~Abstract() {}

		//@}


		/*!
		** \brief Name of the Gfx back-end
		*/
		virtual String name() const = 0;

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
		** \brief Get if the engine is ready
		*/
		virtual bool ready() const = 0;

		/*!
		** \brief Run the device
		*/
		virtual void run() = 0;

		sint32 fps() const {return pFPS;}

	protected:
		sint32 pFPS;

	}; // class Abstract



} // namespace Gfx
} // namespace Private
} // namespace Yuni



#endif // __YUNI_PRIVATE_GFX3D_ABSTRACT_H__
