#
# YUNI_INCLUDE
#

#
# The common paths for Yuni headers
#
LIST(APPEND YUNI_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/..")
LIBYUNI_CONFIG_INCLUDE_PATH("core" "${CMAKE_CURRENT_SOURCE_DIR}/..")
LIBYUNI_CONFIG_LIB_PATH("core" "${LIBRARY_OUTPUT_PATH}")


IF(APPLE)
	# Frameworks
	FIND_LIBRARY(FRAMEWORK_COREFOUNDATION NAMES CoreFoundation)
	FIND_LIBRARY(FRAMEWORK_COCOA NAMES Cocoa)
	FIND_LIBRARY(FRAMEWORK_IOKIT NAMES IOKit)
ENDIF(APPLE)


LIBYUNI_CONFIG_LIB("core"       "yuni-static-core")
IF(APPLE)
	LIBYUNI_CONFIG_CFLAG("core"	"-fvisibility=hidden")
ENDIF(APPLE)
LIBYUNI_CONFIG_LIB("tests"      "yuni-static-tests")
LIBYUNI_CONFIG_LIB("algorithms" "yuni-static-algorithms")

LIBYUNI_CONFIG_LIB("display"    "yuni-static-device-display")
LIBYUNI_CONFIG_DEPENDENCY("display" "devices") # gfx-core is required
LIBYUNI_CONFIG_LIB("mouse"      "yuni-static-device-mouse")
LIBYUNI_CONFIG_DEPENDENCY("mouse" "devices") # gfx-core is required
LIBYUNI_CONFIG_LIB("keyboard"   "yuni-static-device-keyboard")
LIBYUNI_CONFIG_DEPENDENCY("keyboard" "devices") # gfx-core is required

LIBYUNI_CONFIG_LIB("net"        "yuni-static-net")

LIBYUNI_CONFIG_LIB("gfx"        "yuni-static-gfx-core")

LIBYUNI_CONFIG_LIB("gfx3d"      "yuni-static-gfx3d-core")
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "gfx") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "display") # gfx-core is required
LIBYUNI_CONFIG_LIB("gfx3d"      "yuni-static-device-display") # device-display is required

LIBYUNI_CONFIG_LIB("script"     "yuni-static-script")
LIBYUNI_CONFIG_DEPENDENCY("lua" "script")

LIBYUNI_CONFIG_DEFINITION("core" "YUNI_LIBRARY_STATIC")



#
# Core
#
IF(NOT YUNI_STATIC_CORE)
	Set(YUNI_STATIC_CORE yuni-static-core)
ELSE(NOT YUNI_STATIC_CORE)
	LIST(INSERT YUNI_STATIC_CORE 0 yuni-static-core)
ENDIF(NOT YUNI_STATIC_CORE)
# PThreads (required by `Core`)
DEVPACK_IMPORT_PTHREADS()

# Tests
IF(YUNI_TESTS)
	LIST(APPEND YUNI_STATIC_CORE yuni-static-tests)
ENDIF(YUNI_TESTS)


#
# Algorithms
#
IF(NOT YUNI_STATIC_ALGORITHMS)
	Set(YUNI_STATIC_ALGORITHMS yuni-static-algorithms)
ELSE(NOT YUNI_STATIC_ALGORITHMS)
	LIST(INSERT YUNI_STATIC_ALGORITHMS 0 yuni-static-algorithms)
ENDIF(NOT YUNI_STATIC_ALGORITHMS)


#
# Device::Display
#
IF(YUNI_MODULE_DEVICE_DISPLAY)
	IF(NOT YUNI_STATIC_CORE)
		Set(YUNI_STATIC_CORE yuni-static-device-display)
	ELSE(NOT YUNI_STATIC_CORE)
		LIST(INSERT YUNI_STATIC_CORE 0 yuni-static-device-display)
	ENDIF(NOT YUNI_STATIC_CORE)
	IF(NOT APPLE AND NOT WIN32)
		LIST(APPEND YUNI_STATIC_DEVICE_DISPLAY X11 Xrandr)
		LIBYUNI_CONFIG_LIB("display" "X11")
		LIBYUNI_CONFIG_LIB("display" "Xrandr")
		LIBYUNI_CONFIG_LIB_PATH("display" "/usr/X11R6/lib")
		LINK_DIRECTORIES("/usr/X11R6/lib")
	ENDIF(NOT APPLE AND NOT WIN32)

	IF(APPLE)
		LIST(APPEND YUNI_STATIC_DEVICE_DISPLAY "${FRAMEWORK_COREFOUNDATION}")
		LIST(APPEND YUNI_STATIC_DEVICE_DISPLAY "${FRAMEWORK_COCOA}")
		LIST(APPEND YUNI_STATIC_DEVICE_DISPLAY "${FRAMEWORK_IOKIT}")
		LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_COREFOUNDATION}")
		LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_COCOA}")
		LIBYUNI_CONFIG_FRAMEWORK("display" "${FRAMEWORK_IOKIT}")
	ENDIF(APPLE)

ENDIF(YUNI_MODULE_DEVICE_DISPLAY)

Set(YUNI_STATIC_NET    yuni-static-net)




IF(NOT YUNI_STATIC_GFX_CORE)
	Set(YUNI_STATIC_GFX_CORE yuni-static-gfx-core)
ELSE(NOT YUNI_STATIC_GFX_CORE)
	LIST(INSERT YUNI_STATIC_GFX_CORE 0 yuni-static-gfx-core)
ENDIF(NOT YUNI_STATIC_GFX_CORE)


Set(YUNI_STATIC_GFX3D  yuni-static-gfx3d-core
	${YUNI_STATIC_DEVICE_DISPLAY})
IF(APPLE)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" "${FRAMEWORK_COREFOUNDATION}")
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" "${FRAMEWORK_COCOA}")
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" "${FRAMEWORK_IOKIT}")
ENDIF(APPLE)

Set(YUNI_STATIC_SCRIPT yuni-static-script)

#
# Script
#
IF(YUNI_MODULE_SCRIPT)

	#
	# Lua
	#
	IF(YUNI_EXTERNAL_SCRIPT_LUA)
		DEVPACK_IMPORT_LUA()
	ENDIF(YUNI_EXTERNAL_SCRIPT_LUA)

ENDIF(YUNI_MODULE_SCRIPT)

