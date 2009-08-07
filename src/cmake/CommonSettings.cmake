
#
# CMake Stuff
#
#Set(CMAKE_VERBOSE_MAKEFILE ON)
# Policy
IF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
	cmake_policy(SET CMP0004 OLD)
	cmake_policy(SET CMP0003 NEW)
ENDIF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
Include(CheckIncludeFile)











#
# Command line options for G++ (Debug)
#
# Ex: cmake . -DYUNI_TARGET=release
#
IF("${YUNI_CXX_FLAGS_OVERRIDE}" STREQUAL "")
IF("${YUNI_TARGET}" STREQUAL "release")

	#
	# Build Configuration: Release
	#
	Message(STATUS "Build Configuration: Release")

	IF(NOT WIN32)
		String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
		IF(${VA} EQUAL 0)
			Set(CMAKE_CXX_FLAGS "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2 -Wuninitialized -Wunused-parameter -Winit-self")
			If(APPLE)
				Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
			ENdif(APPLE)
		ENDIF(${VA} EQUAL 0)
	Else(NOT WIN32)
		IF(MINGW)
			Set(CMAKE_CXX_OTHER_FLAGS "-O3 -fomit-frame-pointer -Wextra ")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MINGW)
		IF(MSVC)
			Set(CMAKE_CXX_OTHER_FLAGS "/Ob2 /Ot /O2 /MDd /Oy /MT /GL /GS- /arch:SSE2")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MSVC)
	ENDIF(NOT WIN32)
	ADD_DEFINITIONS("-DNDEBUG") # Remove asserts

Else("${YUNI_TARGET}" STREQUAL "release")

	#
	# Build Configuration: Debug
	#
	Message(STATUS "Build Configuration: Debug")


	IF(NOT WIN32)
		String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
		IF(${VA} EQUAL 0)
			Set(CMAKE_CXX_FLAGS "-g -ggdb2 -Wall -Woverloaded-virtual -Wextra -Wconversion -Wredundant-decls -Wundef -Wcast-align -Wcast-qual -Wfloat-equal -Wunused-parameter")
			If(APPLE)
				Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gfull -fvisibility=hidden")
			ENdif(APPLE)
		ENDIF(${VA} EQUAL 0)
	Else(NOT WIN32)
		IF(MINGW)
			Set(CMAKE_CXX_OTHER_FLAGS "-g2 -Woverloaded-virtual -Wextra -Wconversion")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MINGW)
		IF(MSVC)
			Set(CMAKE_CXX_OTHER_FLAGS "/GR /Ob2 /Ot /MDd /MTd /fp:except /W4")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MSVC)
	ENDIF(NOT WIN32)

EndIF("${YUNI_TARGET}" STREQUAL "release")

ELSE("${YUNI_CXX_FLAGS_OVERRIDE}" STREQUAL "")

	Message(STATUS "C++ flags overriden by settings")
	SET(CMAKE_CXX_FLAGS "${YUNI_CXX_FLAGS_OVERRIDE}")

ENDIF("${YUNI_CXX_FLAGS_OVERRIDE}" STREQUAL "")


#
# PThreads
#
DEVPACK_IMPORT_PTHREADS()


#
# Extra - Bundles
#
SET(MACOSX_BUNDLE_COPYRIGHT "Yuni - 2008/2009")

IF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD}" STREQUAL "")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${YUNI_CXX_FLAGS_OVERRIDE_ADD}")
ENDIF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD}" STREQUAL "")



Message(STATUS "C++ flags `${CMAKE_CXX_FLAGS}`")

