
Message(STATUS "[Module] Device::Display")

LIBYUNI_CONFIG_DEPENDENCY("display" "devices") # gfx-core is required


IF(APPLE)
	# Frameworks
	FIND_LIBRARY(FRAMEWORK_COREFOUNDATION NAMES CoreFoundation)
	FIND_LIBRARY(FRAMEWORK_COCOA NAMES Cocoa)
	FIND_LIBRARY(FRAMEWORK_IOKIT NAMES IOKit)
ENDIF(APPLE)

IF(NOT APPLE AND NOT WIN32 AND NOT HAIKU AND NOT BEOS)
	LIBYUNI_CONFIG_LIB("display" "X11")
	LIBYUNI_CONFIG_LIB("display" "Xrandr")
	LIBYUNI_CONFIG_LIB_PATH("display" "/usr/X11R6/lib")
ENDIF(NOT APPLE AND NOT WIN32 AND NOT HAIKU AND NOT BEOS)

IF(UNIX)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		Include_directories("/usr/local/include")
		LIBYUNI_CONFIG_LIB_PATH("display" "/usr/local/include")
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
ENDIF(UNIX)


IF(APPLE)
	LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_COREFOUNDATION}")
	LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_COCOA}")
	LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_IOKIT}")
ENDIF(APPLE)





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


