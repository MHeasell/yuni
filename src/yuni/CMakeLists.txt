
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


Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/YuniConfig.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")




IF(YUNI_MODULE_CORE)
	# The header yuni.h must be available
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
	# Core
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/core.cmake")
	# GfxCore
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx-core.cmake")
ENDIF(YUNI_MODULE_CORE)




IF(YUNI_MODULE_DEVICES)
	LIBYUNI_CONFIG_LIB("display"    "yuni-static-device-display")
	LIBYUNI_CONFIG_LIB("mouse"      "yuni-static-device-mouse")
	LIBYUNI_CONFIG_DEPENDENCY("mouse" "devices") # gfx-core is required
	LIBYUNI_CONFIG_LIB("keyboard"   "yuni-static-device-keyboard")
	LIBYUNI_CONFIG_DEPENDENCY("keyboard" "devices") # gfx-core is required

	IF(YUNI_MODULE_DEVICE_DISPLAY)
		Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/device-display.cmake")
	ENDIF(YUNI_MODULE_DEVICE_DISPLAY)
	IF(YUNI_MODULE_DEVICE_KEYBOARD)
	ENDIF(YUNI_MODULE_DEVICE_KEYBOARD)
	IF(YUNI_MODULE_DEVICE_MOUSE)
	ENDIF(YUNI_MODULE_DEVICE_MOUSE)
ENDIF(YUNI_MODULE_DEVICES)

IF(YUNI_MODULE_UI)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/ui.cmake")
ENDIF(YUNI_MODULE_UI)

IF(YUNI_MODULE_GFX3D)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx3d.cmake")
ENDIF(YUNI_MODULE_GFX3D)

IF(YUNI_MODULE_AUDIO)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/audio.cmake")
ENDIF(YUNI_MODULE_AUDIO)

IF(YUNI_MODULE_SCRIPT)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/script.cmake")
ENDIF(YUNI_MODULE_SCRIPT)



#
# Module : Network
#
If(YUNI_MODULE_NET)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/net.cmake")
EndIf(YUNI_MODULE_NET)



#IF(YUNI_MODULE_ALGORITHMS)
#	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/algorithms.cmake")
#ENDIF(YUNI_MODULE_ALGORITHMS)




IF(YUNI_TESTS)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/test.cmake")
ENDIF(YUNI_TESTS)


# Generating yuni.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
# Generating version
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.version)


#
# Misc
#
Add_definitions("-DYUNI_LIBRARY_STATIC")
LIBYUNI_CONFIG_DEFINITION("core" "YUNI_LIBRARY_STATIC")
Include_directories(${YUNI_INCLUDE})



YMESSAGE("")

IF("${YUNI_CMAKE_ERROR}" GREATER 0)
	YMESSAGE("")
	YERROR("An error has occured. Aborting.")
	YMESSAGE("")
ENDIF("${YUNI_CMAKE_ERROR}" GREATER 0)
