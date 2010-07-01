


Find_Package(Yuni COMPONENTS core lua)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Script / A Simple Lua Hello World (not functional yet)")
	ADD_EXECUTABLE(script_00_helloworld main.cpp)
ENDIF(Yuni_FOUND)

