#ifndef __YUNI_SYSTEM_DEVICES_DISPLAY_ABSTRACT_H__
# define __YUNI_SYSTEM_DEVICES_DISPLAY_ABSTRACT_H__

# include <vector>
# include <list>
# include "../../yuni.h"
# include "../../string.h"
# include "resolution.h"
# include "../../misc/sharedptr.h"



namespace Yuni
{
namespace System
{
namespace Devices
{
namespace Display
{


	/*!
	** \brief Information about a single Frame Buffer Device
	**
	** This class is not thread-safe
	*/
	class Monitor
	{
	public:
		//! List of monitor
		typedef std::list< SharedPtr<Monitor> >  List;
		//! Vector of monitor
		typedef std::vector< SharedPtr<Monitor> >  Vector;

		//! Handle for a single monitor
		typedef uint32  Handle;
		//! Value for an invalid handle
		static const Handle InvalidHandle = (Handle)(-1);


	public:
		//! \name Constructors and Destructor
		//@{

		//! Default constructor
		Monitor();

		/*!
		** \brief Constructor with values
		**
		** \param nm Name of the monitor
		** \param hwn Handle of the monitor
		** \param p Is the primary display
		** \param a Is hardware-accelerated
		** \param b Is a builtin device
		*/
		Monitor(const String& nm, const Monitor::Handle hwn = InvalidHandle, const bool p = false,
				const bool a = false, const bool b = false);

		//! Constructor by copy
		Monitor(const Monitor& c);
		
		//! Destructor
		virtual ~Monitor();
		
		//@}


		//! \name Handle
		//@{

		/*!
		** \brief Get the index of the current selected monitor
		*/
		Monitor::Handle handle() const {return pHandle;}

		/*!
		** \brief Get if the handle of this monitor is valid
		*/
		bool valid() const {return pHandle != Monitor::InvalidHandle;}

		//@}


		//! \name Identifiers
		//@{

		/*!
		** \brief Get the human readable name of the monitor, if any
		**
		** \return The name of the monitor, or an empty value if not available
		*/
		const String& name() const {return pName;}

		/*!
		** \brief Get an unique id for this screen
		**
		** This ID should be considered as unique only on the local computer.
		** This guid may be useful to load/save settings according the current monitor
		**
		** \return A md5 string
		*/
		const String& guid();

		//@}

		//! \name Informations about the monitor
		//@{

		/*!
		** \brief Get all available resolutions for this screen
		**
		** The returned value is guaranteed to not be empty and to be
		** a sorted descendant list. 
		*/
		const Resolution::Vector& resolutions() const {return pResolutions;}

		/*!
		** \brief Get the recommended resolution for this device
		**
		** It is merely the highest available resolution
		*/
		SharedPtr<Resolution> recommendedResolution() const {return *pResolutions.begin();}

		/*!
		** \brief Get if this monitor is the primary display
		*/
		bool primary() const {return pPrimary;}

		/*!
		** \brief Get if the device is hardware accelerated
		*/
		bool hardwareAcceleration() const {return pHardwareAcceleration;}

		/*!
		** \brief Get if the monitor is a builtin device
		**
		** \note Only available on Mac OS X v10.2 or later
		*/
		bool builtin() const {return pBuiltin;}

		//@}

		/*!
		** \brief Add a new resolution in the list
		**
		** \param[in] r The resolution to add
		** \internal It is a sorted descendant list. The first value must be the highest available value 
		*/
		void addResolution(SharedPtr<Resolution>& r);

	protected:
		//! The index of the monitor
		Monitor::Handle pHandle;
		//! Name of the current
		String pName;
		/*!
		** \brief All resolutions
		** \internal It is a sorted descendant list. The first value must be the highest available value 
		*/
		Resolution::Vector pResolutions;
		//! Primary
		bool pPrimary;
		//! Hardware Acceleration
		bool pHardwareAcceleration;
		//! Builtin device
		bool pBuiltin;

		//! The MD5 for the guid - avoid multiple md5 calculations
		String pMD5Cache;

	}; // class Monitor




} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni

#endif // __YUNI_SYSTEM_DEVICES_DISPLAY_ABSTRACT_H__
