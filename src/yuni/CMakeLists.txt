Project(YUNI)

Message(STATUS "")
Message(STATUS "The Yuni Framework")
Message(STATUS "")

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



IF(NOT WIN32)
	IF(NOT CACHE_OS_INFO)
		EXECUTE_PROCESS(COMMAND "uname" "-mrsv" OUTPUT_VARIABLE OS_INFO OUTPUT_STRIP_TRAILING_WHITESPACE)
		SET(CACHE_OS_INFO "${OS_INFO}" CACHE STRING "Informations about the hardware")
	ENDIF(NOT CACHE_OS_INFO)
	MESSAGE(STATUS "Operating System: ${CACHE_OS_INFO}")
ENDIF(NOT WIN32)



#
# Command line options for G++
#
IF(NOT WIN32)
	String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
	IF(${VA} EQUAL 0)
		Set(CMAKE_CXX_FLAGS "-O3 -g -Wall -Werror -Woverloaded-virtual -Wextra -Wshadow -Wconversion -fstack-check -funroll-loops")
	ENDIF(${VA} EQUAL 0)
Endif(NOT WIN32)
Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")

#
# The target directory for static libs
#
Set(TARGET_LIBS "${PROJECT_SOURCE_DIR}/../../bin/static/")
Set(LIBRARY_OUTPUT_PATH "${TARGET_LIBS}")
Set(ARCHIVE_OUTPUT_DIRECTORY "${TARGET_LIBS}")

#
# The common paths for Yuni headers
#
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I'${PROJECT_SOURCE_DIR}/..'")



Include(FindThreads)
IF(NOT CMAKE_USE_PTHREADS_INIT)
	MESSAGE(FATAL_ERROR "PThreads is required.")
ENDIF(NOT CMAKE_USE_PTHREADS_INIT)



#
# The Yuni Library
#
set(SRC "")

# Misc
set(SRC ${SRC}
				misc/string.h misc/string.cpp
				misc/paths.h misc/paths.cpp
				misc/files.h misc/files.cpp
				misc/version.h misc/version.cpp
				misc/static.h
				misc/math.h)

# Hash
set(SRC ${SRC}
				hash/checksum/abstract.h hash/checksum/abstract.cpp
				hash/checksum/md5.h hash/checksum/md5.cpp
				hash/std.hashmap.h
				hash/key.h
				hash/table.h hash/table.hxx
				hash/dictionary.h)

# System
set(SRC ${SRC}  system/stdint.h system/os.h) 

# Devices
set(SRC ${SRC}
				system/devices/devices.h system/devices/display.cpp
				system/devices/monitor.h system/devices/monitor.cpp
				system/devices/resolution.h system/devices/resolution.cpp) 

# Threads
set(SRC ${SRC}
				threads/mutex.h threads/mutex.cpp
				threads/abstract.thread.h threads/abstract.thread.cpp
				threads/thread.h threads/thread.cpp
				threads/timer.h threads/timer.cpp
				threads/jobs.abstract.h threads/jobs.abstract.cpp
				threads/cpu.cpp)

# Application
set(SRC ${SRC}
				application/abstract.h application/abstract.cpp
				application/console.h application/console.cpp
				application/gfx3d.h application/gfx3d.cpp)

# Gfx
set(SRC ${SRC}
				gfx/device.h gfx/device.cpp
				gfx/point2D.h gfx/point3D.h
				gfx/color.converters.h gfx/color.converters.cpp
				gfx/rgba.h
				gfx/vertex.h gfx/triangle.h gfx/edge.h)

# User Interface
set(SRC ${SRC}
				gfx/ui/window.h gfx/ui/window.cpp
				gfx/ui/component.h gfx/ui/component.cpp)


# External Lib: Irrlicht
#Set(SRC ${SRC}	private/gfx3d/irrlicht/irrlicht-for-yuni.h private/gfx3d/irrlicht/irrlicht-for-yuni.cpp)




add_library(yuni STATIC ${SRC})


