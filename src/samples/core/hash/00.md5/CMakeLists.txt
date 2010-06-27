

Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Compute a MD5 checksum from a string")
	ADD_EXECUTABLE(hash_00_md5 main.cpp)
ENDIF(LibYuni_FOUND)

