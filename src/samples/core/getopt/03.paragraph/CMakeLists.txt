

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Command line Options (GetOpt) / With text paragraph")
	ADD_EXECUTABLE(getopt_03_paragraph main.cpp)
ENDIF(LibYuni_FOUND)

