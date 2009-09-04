


Find_Package(LibYuni COMPONENTS core lua)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Script / A Simple Lua Hello World (not functional yet)")
	ADD_EXECUTABLE(script_00_helloworld main.cpp)
ENDIF(LibYuni_FOUND)

