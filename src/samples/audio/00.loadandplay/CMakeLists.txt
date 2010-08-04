

Find_Package(Yuni COMPONENTS core audio)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	add_definitions(-D__STDC_CONSTANT_MACROS)
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Audio / Load sounds and play them")
	ADD_EXECUTABLE(audio_00_loadandplay 00.loadandplay.cpp)
ENDIF(Yuni_FOUND)

