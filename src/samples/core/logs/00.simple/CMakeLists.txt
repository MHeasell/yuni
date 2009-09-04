

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Logs / 'Hello World' with several verbosity levels")
	ADD_EXECUTABLE(logs_00_simple main.cpp)
ENDIF(LibYuni_FOUND)
