#ifndef __YUNI_SYSTEM_DEVICES_DISPLAY_H__
# define __YUNI_SYSTEM_DEVICES_DISPLAY_H__

# include "../../yuni.h"
# include "../../string.h"
# include "resolution.h"
# include "monitor.h"



namespace Yuni
{
namespace System
{
namespace Devices
{

/*!
** \brief Display device handling
*/
namespace Display
{


	class List
	{
	public:
		List();
		List(const List& c);
		~List() {}

		/*!
		** \brief Refresh informations about the monitors
		*/
		void refresh();

		/*!
		** \brief Get the primary display
		**
		** The result is guaranteed to be valid for use.
		*/
		SharedPtr<Monitor> primary() const {return pPrimary;}

		/*!
		** \brief All available monitors
		*/
		const Monitor::Vector& monitors() const {return pMonitors;}

		/*!
		** \brief Find a monitor by its handle
		**
		** \return A reference to a monitor. Use the method `valid()` to know
		** if the monitor has been found
		**
		** \param hwn The handle to find
		**
		** \see Monitor::valid()
		*/
		SharedPtr<Monitor> findByHandle(const Monitor::Handle hwn) const;

		/*!
		** \brief Find a monitor by its guid
		**
		** \return A reference to a monitor. Use the method `valid()` to know
		** if the monitor has been found
		**
		** \param guid The guid to find
		**
		** \see Monitor::valid()
		*/
		SharedPtr<Monitor> findByGUID(const String& guid) const;


	private:
		//! All available monitors
		Monitor::Vector  pMonitors;
		//! The primary display
		SharedPtr<Monitor> pPrimary;
		//! A null monitor
		SharedPtr<Monitor> pNullMonitor;

	}; // class List



} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni

#endif // __YUNI_SYSTEM_DEVICES_DISPLAY_H__
