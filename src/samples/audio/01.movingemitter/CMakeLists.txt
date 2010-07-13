

Find_Package(Yuni COMPONENTS audio)
IF(Yuni_FOUND)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Yuni_CXXFLAGS}")
	add_definitions(-D__STDC_CONSTANT_MACROS)
	link_libraries("${Yuni_LIBS}")

	Message(STATUS "Sample: Audio / Play a sound on a moving emitter")
	ADD_EXECUTABLE(audio_01_movingemitter 01.movingemitter.cpp)
ENDIF(Yuni_FOUND)

