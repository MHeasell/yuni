
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
# Informations about the system
#
Message(STATUS "System: ${CMAKE_SYSTEM} (${CMAKE_SYSTEM_PROCESSOR})")
If(MSVC)
    Message(STATUS "Compiler: Visual Studio")
EndIF(MSVC)
If(MINGW)
    Message(STATIS "Compiler: MinGW")
EndIf(MINGW)


#
# Command line options for G++
#
IF(NOT WIN32)
	String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
	IF(${VA} EQUAL 0)
		Set(CMAKE_CXX_FLAGS "-O3 -g -Wall -Werror -Woverloaded-virtual -Wextra -Wshadow -Wconversion -fstack-check -funroll-loops")
	ENDIF(${VA} EQUAL 0)
	Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")
Else(NOT WIN32)
	IF(MINGW)
		Set(CMAKE_CXX_OTHER_FLAGS "-Woverloaded-virtual -Wextra -Wshadow -Wconversion -fstack-check -funroll-loops")
		Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
		Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
	ENDIF(MINGW)
	IF(MSVC)
		Set(CMAKE_CXX_OTHER_FLAGS "/GR /WX /Ob2 /Ot /MDd")
		Message(STATUS "Added C++ flags `${CMAKE_CXX_OTHER_FLAGS}`")
		Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_OTHER_FLAGS}")
	ENDIF(MSVC)
ENDIF(NOT WIN32)



#
# PThreads
#
If(WIN32)
    Include_Directories("${PROJECT_SOURCE_DIR}/../../externals/pthreads/win32/include")
Else(WIN32)
    Include(FindThreads)
    IF(NOT CMAKE_USE_PTHREADS_INIT)
	    MESSAGE(FATAL_ERROR "PThreads is required.")
    ENDIF(NOT CMAKE_USE_PTHREADS_INIT)
EndIF(WIN32)


