

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Mathematics / Randomness / Random numbers within a range")
	ADD_EXECUTABLE(math_rn_01_range main.cpp)
ENDIF(LibYuni_FOUND)

