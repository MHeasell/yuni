

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Dictionary with insensitive keys")
	ADD_EXECUTABLE(hash_03_dictionary_insensitive main.cpp)
ENDIF(Yuni_FOUND)

