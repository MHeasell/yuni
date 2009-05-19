
#include <map>
#include <cassert>
#include "../../yuni.h"
#include "display.h"
#ifdef YUNI_OS_MAC
#	include <CoreFoundation/CoreFoundation.h>
#	include <ApplicationServices/ApplicationServices.h>
#endif
#ifdef YUNI_OS_WINDOWS
#	include <windows.h>
#endif

#define YUNI_DEVICE_MAX_DISPLAYS   64



namespace Yuni
{
namespace System
{
namespace Devices
{
namespace Display
{


	namespace
	{

		typedef std::map<uint32, std::map<uint32, uint8> >  OrderedResolutions;
		typedef std::pair< SmartPtr<Monitor>, SmartPtr<OrderedResolutions> > SingleMonitorFound;
		typedef std::vector<SingleMonitorFound> MonitorsFound;


# ifdef YUNI_OS_MAC

#	define GET_MODE_WIDTH(mode) GetDictionaryLong((mode), kCGDisplayWidth)
#	define GET_MODE_HEIGHT(mode) GetDictionaryLong((mode), kCGDisplayHeight)
#	define GET_MODE_REFRESH_RATE(mode) GetDictionaryLong((mode), kCGDisplayRefreshRate)
#	define GET_MODE_BITS_PER_PIXEL(mode) GetDictionaryLong((mode), kCGDisplayBitsPerPixel)

#	define GET_MODE_SAFE_FOR_HARDWARE(mode) GetDictionaryBoolean((mode), kCGDisplayModeIsSafeForHardware)
#	define GET_MODE_STRETCHED(mode) GetDictionaryBoolean((mode), kCGDisplayModeIsStretched)

		/*!
		 * \brief Get a boolean from the dictionary
		 *
		 * \param theDict The dictionary
		 * \param key The key to read its value
		 */
		Boolean GetDictionaryBoolean(CFDictionaryRef theDict, const void* key)
		{
			Boolean value(false);
			CFBooleanRef boolRef = (CFBooleanRef) CFDictionaryGetValue(theDict, key);
			if (NULL != boolRef)
				value = CFBooleanGetValue(boolRef);
			return value;
		}

		/*!
		 * \brief Get a long from the dictionary
		 *
		 * \param theDict The dictionary
		 * \param key The key to read its value
		 */
		long GetDictionaryLong(CFDictionaryRef theDict, const void* key)
		{
			// get a long from the dictionary
			long value(0);
			CFNumberRef numRef = (CFNumberRef) CFDictionaryGetValue(theDict, key);
			if (NULL != numRef)
				CFNumberGetValue(numRef, kCFNumberLongType, &value);
			return value;
		}

		void cocoaGetAllAvailableModesUseful(CGDirectDisplayID display, SmartPtr<OrderedResolutions>& res)
		{
			// get a list of all possible display modes for this system.
			CFArrayRef availableModes = CGDisplayAvailableModes(display);
			unsigned int numberOfAvailableModes = CFArrayGetCount(availableModes);
			if (!numberOfAvailableModes)
				return;

			// get the current bits per pixel.
			long currentModeBitsPerPixel = GET_MODE_BITS_PER_PIXEL(CGDisplayCurrentMode(display));

			for (unsigned int i= 0; i<numberOfAvailableModes; ++i)
			{
				// look at each mode in the available list
				CFDictionaryRef mode = (CFDictionaryRef)CFArrayGetValueAtIndex(availableModes, i);

				// we are only interested in modes with the same bits per pixel as current.
				// to allow for switching from fullscreen to windowed modes.
				// that are safe for this hardward
				// that are not stretched.
				Boolean safeForHardware = GET_MODE_SAFE_FOR_HARDWARE(mode);
				Boolean stretched = GET_MODE_STRETCHED(mode);
				int bitsPerPixel = GET_MODE_BITS_PER_PIXEL(mode);

				if ((bitsPerPixel == currentModeBitsPerPixel) && safeForHardware && !stretched)
					(*res)[GET_MODE_WIDTH(mode)][GET_MODE_HEIGHT(mode)] = (uint8) bitsPerPixel;
			}
		}

		/*!
		 * \brief Get all monitor and their resolutions from the Cocoa Framework
		 *
		 * \link http://developer.apple.com/documentation/GraphicsImaging/Reference/Quartz_Services_Ref/Reference/reference.html#//apple_ref/doc/uid/TP30001070-CH202-F17085
		 * \link http://developer.apple.com/documentation/GraphicsImaging/Conceptual/QuartzDisplayServicesConceptual/Articles/DisplayInfo.html#//apple_ref/doc/uid/TP40004272
		 * \link http://developer.apple.com/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_quartz_services/chapter_952_section_2.html
		 */
		void refreshForCocoa(MonitorsFound& lst)
		{
			// All displays
			CGDirectDisplayID displayArray [YUNI_DEVICE_MAX_DISPLAYS];
			// The count of display
			CGDisplayCount numDisplays;

			// Grab all available displays
			CGGetOnlineDisplayList(YUNI_DEVICE_MAX_DISPLAYS, displayArray, &numDisplays);
			if (!numDisplays)
				return;
			// Browse all displays
			for (unsigned int i = 0; i < numDisplays; ++i)
			{
				// int width  = CGDisplayPixelsWide(displayArray[i]);
				// int height = CGDisplayPixelsHigh(displayArray[i]);
				// int bpp    = CGDisplayBitsPerPixel(displayArray[i]);
				bool mainDisplay = CGDisplayIsMain(displayArray[i]);
				bool builtin     = CGDisplayIsBuiltin(displayArray[i]);
				bool ha          = CGDisplayUsesOpenGLAcceleration(displayArray[i]);
				// uint32_t modelNumber = CGDisplayModelNumber(displayArray[i]);
				// uint32_t serialNumer = CGDisplaySerialNumber(displayArray[i]);

				SmartPtr<Monitor> newMonitor(new Monitor("", (Monitor::Handle)displayArray[i], mainDisplay, ha, builtin));
				SmartPtr<OrderedResolutions> res(new OrderedResolutions());
				cocoaGetAllAvailableModesUseful(displayArray[i], res);
				// Add it to the list
				lst.push_back(SingleMonitorFound(newMonitor, res));
			}
		}

# endif


# ifdef YUNI_OS_WINDOWS

		// Use the following structure rather than DISPLAY_DEVICE, since some old 
		// versions of DISPLAY_DEVICE are missing the last two fields and this can
		// cause problems with EnumDisplayDevices on Windows 2000.
		struct DISPLAY_DEVICE_FULL
		{
			DWORD  cb;
			TCHAR  DeviceName[32];
			TCHAR  DeviceString[128];
			DWORD  StateFlags;
			TCHAR  DeviceID[128];
			TCHAR  DeviceKey[128];
		};


		static SingleMonitorFound* findMonitor(const Yuni::String& monitorName, MonitorsFound& lst)
		{
			uint16 i;
			for (i = 0; i < lst.size() && lst[i].first->name() != monitorName; ++i)
				;
			return (i >= lst.size()) ? NULL : &lst[i];
		}

		static void addResolutions(DISPLAY_DEVICE_FULL& device, SmartPtr<OrderedResolutions> res)
		{
			DEVMODE devMode;
			devMode.dmSize = sizeof (DEVMODE);
			devMode.dmDriverExtra = 32;

			for (uint16 i = 0; EnumDisplaySettings(device.DeviceName, i, &devMode); ++i)
				(*res)[devMode.dmPelsWidth][devMode.dmPelsHeight] = (uint8)devMode.dmBitsPerPel;
		}

		/*!
		** \brief Windows-specific implementation for the monitor / resolution list refresh
		*/
		static void refreshForWindows(MonitorsFound& lst)
		{
			uint16 countMonitors = 0;
			DISPLAY_DEVICE_FULL displayDevice;
			displayDevice.cb = sizeof (DISPLAY_DEVICE_FULL);
			// Loop on all display devices
			for (uint16 countDevices = 0; EnumDisplayDevices(NULL, countDevices, (DISPLAY_DEVICE*)&displayDevice, 0); ++countDevices)
			{
				// Ignore mirrored displays
				if (!(displayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) && (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
				{
					DISPLAY_DEVICE_FULL monitorDisplayDevice;
					monitorDisplayDevice.cb = sizeof (DISPLAY_DEVICE_FULL);
					// A second call is necessary to get the monitor name associated with the display
					EnumDisplayDevices(displayDevice.DeviceName, 0, (DISPLAY_DEVICE*)&monitorDisplayDevice, 0);
					bool mainDisplay = (0 != (displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE));

					// Check if we have already stored info on this monitor
					SingleMonitorFound* monitorWithRes = findMonitor(monitorDisplayDevice.DeviceString, lst);
					bool newMonitor = (NULL == monitorWithRes);
					SmartPtr<Monitor> monitor;
					SmartPtr<OrderedResolutions> res;
					if (newMonitor)
					{
						// Create the new monitor
						monitor = new Monitor(monitorDisplayDevice.DeviceString, (Monitor::Handle)countMonitors++, mainDisplay, true, true);
						res = new OrderedResolutions();
					}
					else
					{
						monitor = monitorWithRes->first;
						res = monitorWithRes->second;
					}

					// Add associated resolutions
					addResolutions(displayDevice, res);

					// Add the monitor and its resolutions to the list if necessary
					if (newMonitor)
						lst.push_back(SingleMonitorFound(monitor, res));
					if (countDevices > YUNI_DEVICE_MAX_DISPLAYS)
						break;
				}
			}
		}

# endif

	} // anonymous namespace






	List::List()
		:pNullMonitor(new Monitor("Fail-safe Device"))
	{
		// Initializing the null monitor
		SmartPtr<Resolution> r640x480(new Resolution(640, 480, 32));
		SmartPtr<Resolution> r800x600(new Resolution(800, 600, 32));
		// The first result must be the highest resolution
		pNullMonitor->addResolution(r800x600);
		pNullMonitor->addResolution(r640x480);

		// Refreshing
		refresh();
	}

	List::List(const List& c)
		:pMonitors(c.pMonitors), pPrimary(c.pPrimary), pNullMonitor(c.pNullMonitor)
	{}


	void List::refresh()
	{
		// No [primary] device for now
		pPrimary = pNullMonitor;
		pMonitors.clear();

		MonitorsFound lst; // all monitors found

# ifdef YUNI_OS_MAC
		refreshForCocoa(lst);
# else
#  ifdef YUNI_OS_WINDOWS
		refreshForWindows(lst);
#  endif
# endif

		for (MonitorsFound::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			if ((it->second)->empty()) // no available resolutions
				continue;
			SmartPtr<Monitor>& monitor = it->first;
			// Browse all resolutions
			for (OrderedResolutions::reverse_iterator j = (it->second)->rbegin(); j != (it->second)->rend(); ++j)
			{
				for (std::map<uint32, uint8>::reverse_iterator k = j->second.rbegin(); k != j->second.rend(); ++k)
				{
					SmartPtr<Resolution> resolution(new Resolution(j->first, k->first, k->second));
					monitor->addResolution(resolution);
				}
			}
			if (!monitor->resolutions().empty()) // at least one resolution
			{
				pMonitors.push_back(monitor);
				if (monitor->primary())
					pPrimary = monitor;
			}
		}
		// No available monitor/resolution
		// The list must not be empty
		if (pMonitors.empty())
			pMonitors.push_back(pNullMonitor);
	}


	SmartPtr<Monitor> List::findByHandle(const Monitor::Handle hwn) const
	{
		for (Monitor::Vector::const_iterator it = pMonitors.begin(); it != pMonitors.end(); ++it)
		{
			if (hwn == (*it)->handle())
				return *it;
		}
		return pNullMonitor;
	}


	SmartPtr<Monitor> List::findByGUID(const String& guid) const
	{
		for (Monitor::Vector::const_iterator it = pMonitors.begin(); it != pMonitors.end(); ++it)
		{
			if (guid == (*it)->guid())
				return *it;
		}
		return pNullMonitor;
	}



} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni


