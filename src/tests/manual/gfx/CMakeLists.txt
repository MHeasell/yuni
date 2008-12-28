
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(manual-gfx-marchingcubes MACOSX_BUNDLE main.cpp)
SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Test - Marching Cubes")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "yunihw")
SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
target_link_libraries(manual-gfx-marchingcubes  ${YUNI_STATIC_CORE} ${YUNI_STATIC_GFX3D})


