
If(APPLE)
	LINK_LIBRARIES("-framework Foundation -framework AppKit -framework Cocoa -framework Carbon -framework OpenGL")
EndIf(APPLE)

ADD_EXECUTABLE(appl_02_gfx3d_fps MACOSX_BUNDLE main.cpp)
SET(MACOSX_BUNDLE_BUNDLE_NAME "Yuni - Sample - HelloWorld with FPS")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "yunihw")
SET(MACOSX_BUNDLE_ICON_FILE "sample.icns")
target_link_libraries(appl_02_gfx3d_fps yuni-static)

