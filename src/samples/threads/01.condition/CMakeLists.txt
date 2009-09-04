

Find_Package(LibYuni COMPONENTS core)
IF(LibYuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibYuni_CXXFLAGS}")
	link_libraries("${LibYuni_LIBS}")

	Message(STATUS "Sample: Multi-Threading / Using Condition Variable for Thread Synchronization")
	ADD_EXECUTABLE(threads_01_condition main.cpp)
ENDIF(LibYuni_FOUND)

