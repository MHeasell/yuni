
Find_Package(Yuni COMPONENTS core gfx3d)
IF(LibYuni_FOUND)
	Message(STATUS "Sample: Application / Gfx3D - Hello World")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	ADD_EXECUTABLE(appl_01_gfx3d WIN32 MACOSX_BUNDLE main.cpp)
	SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${YUNI_VERSION_STRING}")
	SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")

ENDIF(LibYuni_FOUND)

