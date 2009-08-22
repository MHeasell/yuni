
IF(YUNI_MODULE_GFX3D)
	include_directories(${YUNI_INCLUDE})
	ADD_EXECUTABLE(ui_00_helloworld main.cpp)
	target_link_libraries(ui_00_helloworld ${YUNI_STATIC_CORE} ${YUNI_STATIC_GFX3D})
	add_dependencies(samples ui_00_helloworld)
ENDIF(YUNI_MODULE_GFX3D)
