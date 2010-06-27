

Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Events / Simple event management")
	ADD_EXECUTABLE(events_00_simple main.cpp)
ENDIF(LibYuni_FOUND)

