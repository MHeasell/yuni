Project(YUNI-SAMPLES CXX)

Message(STATUS "")
Message(STATUS "Samples")
Message(STATUS "")
CMake_minimum_required(VERSION 2.6)


Include("${CMAKE_CURRENT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(application)
ADD_SUBDIRECTORY(sharedptr)
ADD_SUBDIRECTORY(colors)
ADD_SUBDIRECTORY(devices)
ADD_SUBDIRECTORY(hash)
ADD_SUBDIRECTORY(threads)
ADD_SUBDIRECTORY(events)
#ADD_SUBDIRECTORY(ui)

