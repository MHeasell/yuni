#ifndef __YUNI_SYSTEM_SCREEN_H__
# define __YUNI_SYSTEM_SCREEN_H__

# include <vector>
# include "../../yuni.h"
# include "../../string.h"



namespace Yuni
{
namespace System
{
namespace Devices
{


	/*!
	** \brief Information about a single monitor
	**
	** This class is not thread-safe
	*/
	class Monitor
	{
	public:
		//! Handle for a single monitor
		typedef uint16  Handle;
		//! Value for an invalid handle
		static const Handle InvalidHandle = (Handle)(-1);



		/*!
		** \brief Screen/Monitor resolution
		*/
		class Resolution
		{
		public:
			//! Vector of resolutions
			typedef std::vector<Resolution>  Vector;

		public:
			//! \name Constructors
			//@{
			//! Default constructors
			Resolution() : pWidth(640), pHeight(480) {} // Default valid values
			//! Constructor by copy
			Resolution(const Resolution& c) : pWidth(c.pWidth), pHeight(c.pHeight) {}
			//@}

			//! The width of the monitor/screen
			uint16 width() const {return pWidth;}
			//! The height of the monitor/screen
			uint16 height() const {return pHeight;}

		private:
			//! Height of the screen
			uint16 pWidth;
			//! Width of the screen
			uint16 pHeight;

		}; // class Resolution



	public:
		//! \name Constructors and Destructor
		//@{
		//! Default constructor
		Monitor() : pHandle(Monitor::InvalidHandle) {}
		//! Constructor with a given handle
		explicit Monitor(const Monitor::Handle h) :pHandle(h) {}
		//! Destructor
		~Monitor();
		//@}

		/*!
		** \brief Get the index of the current selected monitor
		*/
		Monitor::Handle handle() const {return pHandle;}
		/*!
		** \brief Get if the handle of this monitor is valid
		*/
		bool isValid() const {return pHandle != Monitor::InvalidHandle;}

		/*!
		** \brief Get the name of the monitor, if any
		**
		** \return The name of the monitor, or an empty value if not available
		*/
		String name() const {return pName;}

		/*!
		** \brief Get an unique id for this screen
		**
		** This ID should be considered as unique only on the local computer.
		** This guid may be useful to load/save settings according the current monitor
		**
		** \return A md5 string
		*/
		String guid() const;

	private:
		//! The index of the monitor
		Monitor::Handle pHandle;
		//! Name of the current
		String pName;
		//! All resolutions
		Resolution::Vector pResolutions;

	}; // class Monitor





	/*!
	** \brief Informations about all available monitors
	*/
	class Monitors
	{
	public:
		//! List of monitors
		typedef std::vector<Monitor>  MonitorList;

	public:
		/*!
		** \brief Get the number of available monitors
		*/
		static Monitor::Handle Count();

		/*!
		** \brief Get the handle of the primary monitor
		*/
		static Monitor::Handle Primary();

		/*!
		** \brief Find all available monitors
		**
		** \param[out] list The list of all monitors
		** \return True if the operation has succeeded, False otherwise
		*/
		static bool FindAll(MonitorList& list);

	}; // class Monitors



} // namespace Devices
} // namespace System
} // namespace Yuni

#endif // __YUNI_SYSTEM_SCREEN_H__
