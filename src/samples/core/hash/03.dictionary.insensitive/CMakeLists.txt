

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Dictionary with insensitive keys")
	ADD_EXECUTABLE(hash_03_dictionary_insensitive main.cpp)
ENDIF(LibYuni_FOUND)

