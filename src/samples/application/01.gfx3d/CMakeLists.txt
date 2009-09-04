
IF(YUNI_MODULE_GFX3D)

Find_Package(LibYuni COMPONENTS core gfx3d)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	ADD_EXECUTABLE(appl_01_gfx3d WIN32 MACOSX_BUNDLE main.cpp)
	SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${YUNI_VERSION_STRING}")
	SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
	add_dependencies(samples appl_01_gfx3d)

ELSE(LibYuni_FOUND)
	MESSAGE(SEND_ERROR "Impossible to find the yuni framework with the required modules")
ENDIF(LibYuni_FOUND)

ENDIF(YUNI_MODULE_GFX3D)
