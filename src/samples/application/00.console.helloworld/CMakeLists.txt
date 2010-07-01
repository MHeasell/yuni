
Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Application / Console - Hello world")
	ADD_EXECUTABLE(appl_00_console main.cpp)

ENDIF(Yuni_FOUND)
