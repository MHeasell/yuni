
Message(STATUS "[Module] Device::Display")

# Devices
Set(SRC_DEVICE_DISPLAY
		device/display/list/list.h device/display/list/list.cpp
		device/display/list/list.hxx device/display/list.h
		device/display/list/windows.hxx device/display/list/macosx.hxx
		device/display/list/linux.hxx
		device/display/monitor.h device/display/monitor.cpp
		device/display/resolution.h device/display/resolution.cpp)
source_group(Devices\\Display FILES ${SRC_DEVICE_DISPLAY})



Add_Library(yuni-static-device-display STATIC
			yuni.h
			${SRC_DEVICE_DISPLAY}
)
target_link_libraries(yuni-static-device-display yuni-static-core)


