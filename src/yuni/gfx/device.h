#ifndef __YUNI_GFX_DEVICE_H__
# define __YUNI_GFX_DEVICE_H__

# include <iostream>
# include "../yuni.h"
# include "../core/smartptr/smartptr.h"
# include "../device/display/resolution.h"
# include "../device/display/monitor.h"



namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief Informations about a 3D device
	** \ingroup Gfx
	*/
	class Device
	{
	public:
		typedef SmartPtr<Device> Ptr;

	public:
		enum Type
		{
			//! Null Device
			ygdtNull = 0,
			//! Software renderer
			ygdtSoftware,
			//! OpenGL
			ygdtOpenGL,
			//! Microsoft DirectX device (version 9)
			ygdtDirectX9,
			//! Microsoft DirectX device (version 8)
			ygdtDirectX8
		};

		//! The default type according the plateform
		static const Type DefaultType;


		//! \name Device type conversions
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
		//! Get if the fullscreen mode should be used
		bool fullscreen() const {return pFullscreen;}
		//! Set the fullscreen mode
		void fullscreen(const bool f);
		//! Toggle the fullscreen mode
		bool toggleFullscreen();

		//@}

		//! \name The monitor to use
		//@{

		/*!
		** \brief Monitor
		*/
		Yuni::Device::Display::Monitor::Ptr monitor() const {return pMonitor;}

		/*!
		** \brief Set the monitor to use
		*/
		void monitor(const Yuni::Device::Display::Monitor::Ptr& m);

		//@}


		//! \name The Display resolution
		//@{

		/*!
		** \brief Screen resolution
		*/
		Yuni::Device::Display::Resolution::Ptr resolution() const
		{return pResolution;}

		/*!
		** \brief Set the screen resolution
		*/
		void resolution(const Yuni::Device::Display::Resolution::Ptr& r);

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
		bool stencilbuffer() const {return pStencilbuffer;}

		/*!
		** \brief Set the stencilbuffer mode for drawing shadows
		*/
		void stencilbuffer(const bool s);

		//@}

		//! \name VSync (only useful in the fullscreen mode)
		//@{
		//! Get if the VSync should be used
		bool vsync() const {return pVSync;}
		//! Set the VSync mode
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

		//! \name Stream printing
		//@{

		/*!
		** \brief Print the point
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const;

		//@}

	private:
		//! If changes are allowed or not
		bool pLocked;
		//! Type of the device
		Type pType;
		//! The monitor
		Yuni::Device::Display::Monitor::Ptr pMonitor;
		//! The resolution
		Yuni::Device::Display::Resolution::Ptr pResolution;
		//! Fullscreen
		bool pFullscreen;
		//! Stencilbuffer
		bool pStencilbuffer;
		//! vsync
		bool pVSync;

	}; // class Device




} // namespace Gfx
} // namespace Yuni




//! \name Operator overload for stream printing
//@{

inline std::ostream& operator << (std::ostream& out, const Yuni::Gfx::Device& rhs)
{ return rhs.print(out); }
inline std::ostream& operator << (std::ostream& out, const Yuni::SmartPtr<Yuni::Gfx::Device>& rhs)
{ return rhs->print(out); }


//@}


#endif // __YUNI_GFX_DEVICE_H__
