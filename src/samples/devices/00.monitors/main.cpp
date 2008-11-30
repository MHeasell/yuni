
#include <yuni/yuni.h>
#include <yuni/system/devices/display.h>
#include <iostream>


using namespace Yuni;


void title(const String& t)
{
	std::cout << std::endl << "--- " << t << " ---" << std::endl << std::endl;
}


void printMonitor(SharedPtr<System::Devices::Display::Monitor> monitor)
{
	// The name of the monitor
	std::cout << "Name: " << (monitor->name().empty() ? "<Unknown>" : monitor->name());

	// Its GUID
	std::cout << ", guid:" << monitor->guid();
	if (monitor->primary())
		std::cout << ", primary";
	if (monitor->hardwareAcceleration())
		std::cout << ", Hardware-Accelerated";
	std::cout << std::endl;

	// All resolutions
	System::Devices::Display::Resolution::Vector::const_iterator it;
	for (it = monitor->resolutions().begin(); it != monitor->resolutions().end(); ++it)
	{
		// SharedPtr<System::Devices::Display::Resolution> resolution(*it);
		std::cout << "  . " << (*it)->toString() << std::endl;
	}
}



int main(void)
{
	System::Devices::Display::List allDisplays;

	// The primary monitor
	title("The primary display");
	printMonitor(allDisplays.primary());

	// All available monitors
	title("All available displays, the primary display included");
	System::Devices::Display::Monitor::Vector::const_iterator it;
	for (it = allDisplays.monitors().begin(); it != allDisplays.monitors().end(); ++it)
	{
		printMonitor(*it);
	}

	std::cout << std::endl;
	return 0;
}
