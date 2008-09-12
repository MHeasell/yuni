
#include <map>
#include "../../yuni.h"
#include "display.h"
#ifdef YUNI_OS_MAC
#	include <CoreFoundation/CoreFoundation.h>
#	include <ApplicationServices/ApplicationServices.h>
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
		typedef std::pair< SharedPtr<Monitor>, SharedPtr<OrderedResolutions> > SingleMonitorFound;
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

		void cocoaGetAllAvailableModesUseful(CGDirectDisplayID display, SharedPtr<OrderedResolutions>& res) 
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

				SharedPtr<Monitor> newMonitor(new Monitor("", (Monitor::Handle)displayArray[i], mainDisplay, ha, builtin));
				SharedPtr<OrderedResolutions> res(new OrderedResolutions());
				cocoaGetAllAvailableModesUseful(displayArray[i], res);
				// Add it to the list
				lst.push_back(SingleMonitorFound(newMonitor, res));
			}
		}

# endif
	} // anonymous namespace






	List::List()
		:pNullMonitor(new Monitor("Fail-safe Device"))
	{
		// Initializing the null monitor
		SharedPtr<Resolution> r640x480(new Resolution(640, 480, 32));
		SharedPtr<Resolution> r800x600(new Resolution(800, 600, 32));
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
# endif

		for (MonitorsFound::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			if ((it->second)->empty()) // no available resolutions
				continue;
			SharedPtr<Monitor>& monitor = it->first;
			// Browse all resolutions
			for (OrderedResolutions::reverse_iterator j = (it->second)->rbegin(); j != (it->second)->rend(); ++j)
			{
				for (std::map<uint32, uint8>::reverse_iterator k = j->second.rbegin(); k != j->second.rend(); ++k)
				{
					SharedPtr<Resolution> resolution(new Resolution(j->first, k->first, k->second));
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


	SharedPtr<Monitor> List::findByHandle(const Monitor::Handle hwn) const
	{
		for (Monitor::Vector::const_iterator it = pMonitors.begin(); it != pMonitors.end(); ++it)
		{
			if (hwn == (*it)->handle())
				return *it;
		}
		return pNullMonitor;
	}


	SharedPtr<Monitor> List::findByGUID(const String& guid) const
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


