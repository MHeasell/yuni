

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Mathematics / Randomness / Typical use of a random number generator")
	ADD_EXECUTABLE(math_rn_00_simple main.cpp)
ENDIF(LibYuni_FOUND)

