

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / IO / Iterating through a folder")
	ADD_EXECUTABLE(io_00_iterate main.cpp)
ENDIF(LibYuni_FOUND)

