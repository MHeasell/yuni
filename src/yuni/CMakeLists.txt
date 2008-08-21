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
# Command line options for G++
#
String(LENGTH "${CMAKE_CXX_FLAGS}" VA)
IF(${VA} EQUAL 0)
    Set(CMAKE_CXX_FLAGS "-O3 -g -Wall -Werror -Woverloaded-virtual -Wextra -Wshadow -Wconversion -fstack-check")
ENDIF(${VA} EQUAL 0)
Message(STATUS "Default C++ flags set to `${CMAKE_CXX_FLAGS}`")

#
# The target directory for static libs
#
Set(TARGET_LIBS "${PROJECT_SOURCE_DIR}/../../bin/libs/${CMAKE_SYSTEM_NAME}")
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
set(SRC ${SRC}  misc/string.h misc/string.cpp
                misc/paths.h misc/paths.cpp
                misc/files.h misc/files.cpp
                misc/version.h misc/version.cpp)

# Hash
set(SRC ${SRC}  hash/abstract.h hash/abstract.cpp
                hash/md5.h hash/md5.cpp
                hash/key.h
                hash/table.h hash/table.hxx
                hash/dictionary.h)

# System
set(SRC ${SRC}  system/stdint.h system/os.h) 

# Threads
set(SRC ${SRC}  threads/mutex.h threads/mutex.cpp
                threads/abstract.thread.h threads/abstract.thread.cpp
                threads/thread.h threads/thread.cpp
                threads/timer.h threads/timer.cpp
                threads/jobs.abstract.h threads/jobs.abstract.cpp
                threads/cpu.cpp)

# Application
set(SRC ${SRC}  application/abstract.h application/abstract.cpp
                application/console.h application/console.cpp)


add_library(yuni STATIC ${SRC})

