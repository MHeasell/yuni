
IF(YUNI_MODULE_GFX_CORE)
	Message(STATUS "Sample: Devices / List all monitors")
	include_directories(${YUNI_INCLUDE})
	ADD_EXECUTABLE(devices_00_monitors main.cpp)
	target_link_libraries(devices_00_monitors ${YUNI_STATIC_CORE} ${YUNI_STATIC_DEVICE_DISPLAY})
ENDIF(YUNI_MODULE_GFX_CORE)
