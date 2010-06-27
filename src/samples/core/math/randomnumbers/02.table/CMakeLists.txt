

Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Mathematics / Randomness / Random number table")
	ADD_EXECUTABLE(math_rn_02_table main.cpp)
ENDIF(LibYuni_FOUND)

