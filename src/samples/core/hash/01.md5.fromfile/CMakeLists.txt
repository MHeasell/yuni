
Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Hash / Compute a MD5 checksum from a file")
	ADD_EXECUTABLE(hash_01_md5_fromfile main.cpp)
ENDIF(LibYuni_FOUND)

