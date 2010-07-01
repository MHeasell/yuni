
Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Command line Options (GetOpt) / With various types")
	ADD_EXECUTABLE(getopt_01_varioustypes main.cpp)
ENDIF(Yuni_FOUND)

