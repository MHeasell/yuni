
Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Devices / List all monitors")
	ADD_EXECUTABLE(devices_00_monitors main.cpp)
ENDIF(Yuni_FOUND)

