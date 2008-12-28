
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
# Ex: cmake . -DCMAKE_BUILD_TYPE=release 
#
IF("${CMAKE_BUILD_TYPE}" STREQUAL "release")

	#
	# Build Configuration: Release
	#
	Message(STATUS "Build Configuration: Release")

	IF(NOT WIN32)
		String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
		IF(${VA} EQUAL 0)
			Set(CMAKE_CXX_FLAGS "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2")
		ENDIF(${VA} EQUAL 0)
		Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")
	Else(NOT WIN32)
		IF(MINGW)
			Set(CMAKE_CXX_OTHER_FLAGS "-O3 -fomit-frame-pointer -Wextra ")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MINGW)
		IF(MSVC)
			Set(CMAKE_CXX_OTHER_FLAGS "/Ob2 /Ot /O2 /MDd /Wp64 /Oy /MT /GL /GS-")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MSVC)
	ENDIF(NOT WIN32)
	ADD_DEFINITIONS("-DNDEBUG") # Remove asserts

Else("${CMAKE_BUILD_TYPE}" STREQUAL "release")
	
	#
	# Build Configuration: Debug
	#
	Message(STATUS "Build Configuration: Debug")


	IF(NOT WIN32)
		String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
		IF(${VA} EQUAL 0)
			Set(CMAKE_CXX_FLAGS "-ggdb2 -Wall -Woverloaded-virtual -Wextra -Wconversion -fstack-check -funroll-loops")
			If(APPLE)
				Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gfull")
			ENdif(APPLE)
		ENDIF(${VA} EQUAL 0)
		Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")
	Else(NOT WIN32)
		IF(MINGW)
			Set(CMAKE_CXX_OTHER_FLAGS "-g2 -Woverloaded-virtual -Wextra -Wconversion -fstack-check -funroll-loops")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MINGW)
		IF(MSVC)
			Set(CMAKE_CXX_OTHER_FLAGS "/GR /Ob2 /Ot /MDd /MTd /fp:except")
			Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
			Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
		ENDIF(MSVC)
	ENDIF(NOT WIN32)

EndIF("${CMAKE_BUILD_TYPE}" STREQUAL "release")






#
# PThreads
#
Include(FindThreads)
If(CMAKE_USE_WIN32_THREADS_INIT)
	Message(STATUS "Threading Support: PThreads for Windows (via DevPacks)")
	DEVPACK_IMPORT_PTHREADS()
Else(CMAKE_USE_WIN32_THREADS_INIT)
    IF(NOT CMAKE_USE_PTHREADS_INIT)
	    MESSAGE(FATAL_ERROR "PThreads is required.")
    ENDIF(NOT CMAKE_USE_PTHREADS_INIT)
	Link_libraries(${CMAKE_THREAD_LIBS_INIT})
	Message(STATUS "Threading Support: PThreads (${CMAKE_THREAD_LIBS_INIT})")
EndIF(CMAKE_USE_WIN32_THREADS_INIT)


#
# Extra - Bundles
#
SET(MACOSX_BUNDLE_COPYRIGHT "Yuni - 2008/2009")



