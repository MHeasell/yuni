Project(YUNI)

#
# CMake Stuff
#
CMake_minimum_required(VERSION 2.6)
#Set(CMAKE_VERBOSE_MAKEFILE ON)
# Policy
IF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
	cmake_policy(SET CMP0004 OLD)
	cmake_policy(SET CMP0003 NEW)
ENDIF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
Include(CheckIncludeFile)

#
# Check for Threads.
#
Include(FindThreads)

#
# Command line options for G++
#
String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
IF(${VA} EQUAL 0)
	Set(CMAKE_CXX_FLAGS "-O3 -g -Wall -Werror -Woverloaded-virtual -Wextra -Wshadow -Wconversion -fstack-check -funroll-loops")
ENDIF(${VA} EQUAL 0)
Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")

#
# The Yuni library
#
Set(YUNI_STATIC_LIB "${PROJECT_SOURCE_DIR}/../../bin/static/libyuni.a")

#
# The common paths for Yuni headers
#
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I'${PROJECT_SOURCE_DIR}/..'")


ADD_SUBDIRECTORY(sharedptr)
ADD_SUBDIRECTORY(colors)
ADD_SUBDIRECTORY(devices)
ADD_SUBDIRECTORY(application)
ADD_SUBDIRECTORY(hash)
IF(CMAKE_USE_PTHREADS_INIT)
	ADD_SUBDIRECTORY(threads)
ELSE(CMAKE_USE_PTHREADS_INIT)
	MESSAGE(WARNING " PThread support missing, threads samples skipped.")
ENDIF(CMAKE_USE_PTHREADS_INIT)


