

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Multi-Threading / Queue Service basic usage")
	ADD_EXECUTABLE(jobs_00_basic_usage main.cpp)
ENDIF(Yuni_FOUND)

