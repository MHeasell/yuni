#ifndef __YUNI_GFX_DEVICE_H__
# define __YUNI_GFX_DEVICE_H__

# include "../yuni.h"
# include "../sharedptr.h"
# include "../system/devices/resolution.h"
# include "../system/devices/monitor.h"



namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief Informations about a 3D device
	*/
	class Device
	{
	public:
		enum Type
		{
			/*! The Null device */       ygdtNull = 0,
			/*! The Software renderer */ ygdtSoftware,
			/*! The OpenGL device */     ygdtOpenGL,
			/*! The Microsoft DirectX device (version 9) */  ygdtDirectX9,   
			/*! The Microsoft DirectX device (version 8) */  ygdtDirectX8
		};

		//! The default type according the plateform
		static const Type DefaultType;


		//! \name Device type convertions
		//@{

		/*!
		** \brief Convert a Device type into a string
		**
		** \param t The device type to convert
		** \return Its string representation
		**
		** \internal The string representation of the latest version of DirectX
		** should not have a readable version. This ensures that any calls to
		** `stringToType()` will give the latest DirectX version by default
		*/
		static String TypeToString(const Type t);

		/*!
		** \brief Convert a string into a type of device
		**
		** If the convertion could not be done, the default type will be returned.
		**
		** \param s The string to convert
		** \return The type
		*/
		Type StringToType(String s);

		//@}

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Default constructor
		*/
		Device();

		/*!
		** \brief Constructor by Copy
		**
		** \note The new instance won't be locked even if the original one
		** was locked.
		*/
		Device(const Device& c);

		//! Destructor
		~Device();

		//@}

		//! \name Type of the device
		//@{

		/*!
		** \brief Get the current device type
		**
		** \note This type may not be the same than requested
		*/
		Type type() const {return pType;}

		/*!
		** \brief Set the new type to use for the next creation of the device
		**
		** If the type can not be used on the platform, the value will remain untouched
		**
		** \param newType The new type to use
		** \return True if the type is available on the current platform, false otherwise
		*/
		bool type(const Type newType);

		/*!
		** \brief Set the new type to use for the next creation of the device
		**
		** If the type can not be used on the platform, the value will remain untouched
		**
		** \param s The new type to use converted using StringToType()
		** \return True if the type is available on the current platform, false otherwise
		**
		** \see StringToType()
		*/
		bool type(const String& s);

		//@}

		//! \name The Fullscreen mode
		//@{

		/*!
		** \brief Fullscreen
		*/
		bool fullscreen() const {return pFullscreen;}
		//! Set the fullscreen mode
		void fullscreen(const bool f);

		//@}

		//! \name The monitor to use
		//@{

		/*!
		** \brief Monitor
		*/
		const SharedPtr<System::Devices::Display::Monitor>& monitor() const
		{return pMonitor;}

		/*!
		** \brief Set the monitor to use
		*/
		void monitor(const SharedPtr<System::Devices::Display::Monitor>& m);

		//@}
		

		//! \name The Display resolution
		//@{

		/*!
		** \brief Screen resolution
		*/
		const SharedPtr<System::Devices::Display::Resolution>& resolution() const
		{return pResolution;}

		/*!
		** \brief Set the screen resolution
		*/
		void resolution(const SharedPtr<System::Devices::Display::Resolution>& r);

		/*!
		** \brief Set the screen resolution
		**
		** \param w The new width
		** \param h The new height
		** \param d The new bit per pixel
		*/
		void resolution(const uint32 w, const uint32 h, const uint8 d = 32 /*Bits*/);

		//@}

		//! \name The Stencilbuffer mode (for drawing shadows)
		//@{

		/*!
		** \brief Get if we want to use the stencil buffer for drawing shadows
		*/
		bool stencilbuffer() const {return pStencilbuffer; }

		/*!
		** \brief Set the stencilbuffer mode for drawing shadows
		*/
		void stencilbuffer(const bool s);

		//@}

		//! \name VSync (only useful in the fullscreen mode)
		//@{

		/*!
		** \brief VSync
		*/
		bool vsync() const {return pVSync;}

		/*!
		** \brief Set the VSync mode
		*/
		void vsync(const bool v);

		//@}

		//! \name Consistency
		//@{

		/*!
		** \brief Ensures settings are valid
		*/
		void ensuresSettingsAreValid();

		//@}

		//! \name Locks
		//@{

		/*!
		** \brief Get if parameters may be modified
		*/
		bool locked() const {return pLocked;}

		/*!
		** \brief Avoid any further changes 
		*/
		void lock();

		/*!
		** \brief Allow further changes
		**
		** \warning This method should not be used by the Yuni library
		*/
		void unlock();

		//@}


	private:
		//! If changes are allowed or not
		bool pLocked;
		//! Type of the device
		Type pType;
		//! The monitor
		SharedPtr<System::Devices::Display::Monitor> pMonitor;
		//! The resolution
		SharedPtr<System::Devices::Display::Resolution> pResolution;
		//! Fullscreen
		bool pFullscreen;
		//! Stencilbuffer
		bool pStencilbuffer;
		//! vsync
		bool pVSync;

	}; // class Device




} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_DEVICE_H__
