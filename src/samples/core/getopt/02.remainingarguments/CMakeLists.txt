
Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Command line Options (GetOpt) / Remaining arguments")
	ADD_EXECUTABLE(getopt_02_remainingargs main.cpp)
ENDIF(Yuni_FOUND)

