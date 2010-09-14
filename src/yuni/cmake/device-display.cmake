
YMESSAGE(":: [Module] Device::Display")

LIBYUNI_CONFIG_DEPENDENCY("display" "devices") # gfx-core is required


IF(UNIX AND NOT APPLE AND NOT HAIKU AND NOT BEOS)
	find_package(X11)
	LIBYUNI_CONFIG_LIB("display" "X11")
	LIBYUNI_CONFIG_LIB("display" "Xext")
	LIBYUNI_CONFIG_LIB("display" "Xrandr")
	LIBYUNI_CONFIG_LIB_PATH("display" "${X11_LIBRARY_DIR}") 
ENDIF(UNIX AND NOT APPLE AND NOT HAIKU AND NOT BEOS)

IF(UNIX)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
		Include_directories("/usr/local/include")
		LIBYUNI_CONFIG_LIB_PATH("display" "/usr/local/include")
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
ENDIF(UNIX)


IF(APPLE)
	LIBYUNI_CONFIG_FRAMEWORK("display" CoreFoundation)
	LIBYUNI_CONFIG_FRAMEWORK("display" Cocoa)
	LIBYUNI_CONFIG_FRAMEWORK("display" IOKit)
ENDIF(APPLE)





# Devices
Set(SRC_DEVICE_DISPLAY
		device/display/list/list.h
		device/display/list/list.cpp
		device/display/list/list.hxx
		device/display/list.h
		device/display/list/windows.hxx
		device/display/list/macosx.hxx
		device/display/list/linux.hxx
		device/display/monitor.h
		device/display/monitor.cpp
		device/display/resolution.h
		device/display/resolution.cpp)
source_group(Devices\\Display FILES ${SRC_DEVICE_DISPLAY})


Add_Library(yuni-static-device-display STATIC
			yuni.h
			${SRC_DEVICE_DISPLAY}
)

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-device-display PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
INSTALL(TARGETS yuni-static-device-display ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install Device-related headers
INSTALL(
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


