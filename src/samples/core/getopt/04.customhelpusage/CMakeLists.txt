

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Command line Options (GetOpt) / Custom Help usage")
	ADD_EXECUTABLE(getopt_04_customhelpusage main.cpp)
ENDIF(Yuni_FOUND)

