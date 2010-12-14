
YMESSAGE("")
YMESSAGE("Modules")
YMESSAGE("")


# The target directory for static libs
Set(LIBRARY_OUTPUT_PATH      "${CMAKE_CURRENT_BINARY_DIR}/../build/${YUNI_TARGET}/lib")
Set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../build/${YUNI_TARGET}/lib")



#
# Preflight
#
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_OPENGL  0)
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_DIRECTX 0)
Set(YUNI_CMAKE_ERROR 0)


#
# Informations for yuni-config
#
Set(LIBYUNI_CONFIG_ENABLED true)


include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/YuniConfig.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")




if(YUNI_MODULE_CORE)
	# The header yuni.h must be available
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
	# Core
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/core.cmake")
endif()


if(YUNI_MODULE_VFS)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/vfs.cmake")
endif(YUNI_MODULE_VFS)


if(YUNI_MODULE_DEVICES)
	LIBYUNI_CONFIG_LIB("both" "display"    "yuni-static-device-display")
	LIBYUNI_CONFIG_LIB("both" "mouse"      "yuni-static-device-mouse")
	LIBYUNI_CONFIG_DEPENDENCY("mouse" "devices")
	LIBYUNI_CONFIG_LIB("both" "keyboard"   "yuni-static-device-keyboard")
	LIBYUNI_CONFIG_DEPENDENCY("keyboard" "devices")

	if(YUNI_MODULE_DEVICE_DISPLAY)
		include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/device-display.cmake")
	endif()
	if(YUNI_MODULE_DEVICE_KEYBOARD)
	endif()
	if(YUNI_MODULE_DEVICE_MOUSE)
	endif()
endif()

if(YUNI_MODULE_UI)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ui.cmake")
endif()

if(YUNI_MODULE_GFX3D)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx3d.cmake")
endif()

if(YUNI_MODULE_AUDIO)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/audio.cmake")
endif()

if(YUNI_MODULE_SCRIPT)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/script.cmake")
endif()



#
# Module : Network
#
If(YUNI_MODULE_NET)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/net.cmake")
EndIf()



#if(YUNI_MODULE_ALGORITHMS)
#	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/algorithms.cmake")
#endif(YUNI_MODULE_ALGORITHMS)




if(YUNI_TESTS)
	include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/test.cmake")
endif()


# Generating yuni.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
# Generating version
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.version)


#
# Misc
#
add_definitions("-DYUNI_LIBRARY_STATIC")
LIBYUNI_CONFIG_DEFINITION("both" "core" "YUNI_LIBRARY_STATIC")
include_directories(${YUNI_INCLUDE})



YMESSAGE("")

if("${YUNI_CMAKE_ERROR}" GREATER 0)
	YMESSAGE("")
	YERROR("An error has occured. Aborting.")
	YMESSAGE("")
endif()

