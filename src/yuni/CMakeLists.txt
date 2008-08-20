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
    Set(CMAKE_CXX_FLAGS "-O3 -g -Wall -Werror -Woverloaded-virtual -Wextra -Wshadow -Wconversion -Winline -fstack-check")
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



#
# Yuni Modules
#
ADD_SUBDIRECTORY(misc)
ADD_SUBDIRECTORY(hash)
ADD_SUBDIRECTORY(threads)
ADD_SUBDIRECTORY(application)


add_library(yuni STATIC misc/yuni.cpp)
target_link_libraries(yuni
    yuni-misc yuni-application yuni-hash yuni-threads
)

