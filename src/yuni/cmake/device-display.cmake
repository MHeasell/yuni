
YMESSAGE(":: [Module] Device::Display")

LIBYUNI_CONFIG_DEPENDENCY("display" "devices") # devices is required


if(UNIX AND NOT APPLE AND NOT HAIKU AND NOT BEOS)
	find_package(X11)
	LIBYUNI_CONFIG_LIB("display" "X11")
	LIBYUNI_CONFIG_LIB("display" "Xext")
	LIBYUNI_CONFIG_LIB("display" "Xrandr")
	LIBYUNI_CONFIG_LIB_PATH("display" "${X11_LIBRARY_DIR}")
endif(UNIX AND NOT APPLE AND NOT HAIKU AND NOT BEOS)

if(UNIX)
	if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		include_directories("/usr/local/include")
		LIBYUNI_CONFIG_LIB_PATH("display" "/usr/local/include")
	endif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
endif(UNIX)


if(APPLE)
	LIBYUNI_CONFIG_FRAMEWORK("display" CoreFoundation)
	LIBYUNI_CONFIG_FRAMEWORK("display" Cocoa)
	LIBYUNI_CONFIG_FRAMEWORK("display" IOKit)
endif(APPLE)





# Devices
set(SRC_DEVICE_DISPLAY
		device/display/list/list.h
		device/display/list/list.cpp
		device/display/list/list.hxx
		device/display/list.h
		device/display/list/windows.hxx
		device/display/list/macosx.hxx
		device/display/list/linux.hxx
		device/display/monitor.h
		device/display/monitor.hxx
		device/display/monitor.cpp
		device/display/resolution.h
		device/display/resolution.hxx
		device/display/resolution.cpp)
source_group(Devices\\Display FILES ${SRC_DEVICE_DISPLAY})


add_library(yuni-static-device-display STATIC
			yuni.h
			${SRC_DEVICE_DISPLAY}
)

# Setting output path
set_target_properties(yuni-static-device-display PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-device-display ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install Device-related headers
install(
	DIRECTORY device
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)

target_link_libraries(yuni-static-device-display yuni-static-core)


