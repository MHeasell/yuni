
IF(YUNI_MODULE_GFX3D)
	Message(STATUS "Sample: Application / Gfx3D - FPS Counter")
	include_directories(${YUNI_INCLUDE})

	ADD_EXECUTABLE(appl_02_gfx3d_fps WIN32 MACOSX_BUNDLE main.cpp)
	SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld with FPS")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "yunihw")
	SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
	target_link_libraries(appl_02_gfx3d_fps ${YUNI_STATIC_CORE} ${YUNI_STATIC_GFX_CORE} ${YUNI_STATIC_GFX3D})
ENDIF(YUNI_MODULE_GFX3D)
