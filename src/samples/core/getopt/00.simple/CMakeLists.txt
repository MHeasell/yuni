
Message(STATUS "Sample: Core / Command line Options (GetOpt) / Simple option")

Find_Package(LibYuni COMPONENTS core gfx3d)
IF(LibYuni_FOUND)
	MESSAGE(STATUS "The Yuni Framework : ${LibYuni_INFOS}")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	ADD_EXECUTABLE(getopt_00_simple main.cpp)
	add_dependencies(samples getopt_00_simple)

ELSE(LibYuni_FOUND)
	MESSAGE(SEND_ERROR "Impossible to find the yuni framework with the required modules")
ENDIF(LibYuni_FOUND)
