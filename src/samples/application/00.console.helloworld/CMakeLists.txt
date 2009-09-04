
Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Application / Console - Hello world")
	ADD_EXECUTABLE(appl_00_console main.cpp)

ENDIF(LibYuni_FOUND)
