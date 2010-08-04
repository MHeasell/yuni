

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Singleton / Phoenix singleton")
	ADD_EXECUTABLE(singleton_01_phoenix main.cpp)
ENDIF(Yuni_FOUND)

