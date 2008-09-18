
include_directories(${YUNI_INCLUDE})

ADD_EXECUTABLE(appl_01_gfx3d MACOSX_BUNDLE main.cpp)
SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "yunihw")
SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
target_link_libraries(appl_01_gfx3d ${YUNI_LIBRARIES} ${YUNI_EXT_IRRLICHT_LIB})

