
Find_Package(Yuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Mathematics / Randomness / Random number table + Range")
	ADD_EXECUTABLE(math_rn_03_table_plus_range main.cpp)
ENDIF(LibYuni_FOUND)

