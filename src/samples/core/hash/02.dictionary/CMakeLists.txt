

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Simple dictionary management")
	ADD_EXECUTABLE(hash_02_dictionary main.cpp)
ENDIF(Yuni_FOUND)
