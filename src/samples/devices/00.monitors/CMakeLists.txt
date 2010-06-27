
Find_Package(Yuni COMPONENTS core display)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Devices / List all monitors")
	ADD_EXECUTABLE(devices_00_monitors main.cpp)
ENDIF(LibYuni_FOUND)

