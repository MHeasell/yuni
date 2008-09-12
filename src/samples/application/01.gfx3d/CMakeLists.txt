
If(APPLE)
	LINK_LIBRARIES("-framework Cocoa -framework Carbon -framework OpenGL -framework Foundation -framework AppKit")
EndIf(APPLE)

ADD_EXECUTABLE(appl_01_gfx3d main.cpp)
target_link_libraries(appl_01_gfx3d yuni-static)

