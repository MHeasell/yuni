
If(APPLE)
	LINK_LIBRARIES("-framework Cocoa")
EndIf(APPLE)
ADD_EXECUTABLE(devices_00_monitors main.cpp)
target_link_libraries(devices_00_monitors "${YUNI_STATIC_LIB}")

