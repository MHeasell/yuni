
Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Command line Options (GetOpt) / With various types")
	ADD_EXECUTABLE(getopt_01_varioustypes main.cpp)
ENDIF(LibYuni_FOUND)

