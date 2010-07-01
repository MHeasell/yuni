

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Core / Mathematics / Randomness / Random numbers within a range")
	ADD_EXECUTABLE(math_rn_01_range main.cpp)
ENDIF(Yuni_FOUND)

