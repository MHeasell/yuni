
IF(YUNI_MODULE_GFX3D)
	Message(STATUS "Sample: Application / Gfx3D - Hello world")
	include_directories(${YUNI_INCLUDE})

	ADD_EXECUTABLE(appl_01_gfx3d WIN32 MACOSX_BUNDLE main.cpp)
	SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${YUNI_VERSION_STRING}")
	SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
	target_link_libraries(appl_01_gfx3d ${YUNI_STATIC_CORE} ${YUNI_STATIC_GFX_CORE} ${YUNI_STATIC_GFX3D})
	add_dependencies(samples appl_01_gfx3d)
ENDIF(YUNI_MODULE_GFX3D)

