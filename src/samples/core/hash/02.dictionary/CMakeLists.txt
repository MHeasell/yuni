

Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Simple dictionary management")
	ADD_EXECUTABLE(hash_02_dictionary main.cpp)
ENDIF(LibYuni_FOUND)
