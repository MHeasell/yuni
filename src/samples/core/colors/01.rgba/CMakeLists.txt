

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Core / Colors / Conversion between several RGBA color models")
	ADD_EXECUTABLE(color_01_rgba main.cpp)
ENDIF(LibYuni_FOUND)
