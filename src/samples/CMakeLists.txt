Project(YUNI-SAMPLES CXX)

CMake_minimum_required(VERSION 2.6)

IF(POLICY CMP0011)
	CMake_Policy(SET CMP0011 NEW)
ENDIF(POLICY CMP0011)


Message(STATUS "")
Message(STATUS "Samples")
Message(STATUS "")


Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/LibYuniConfig.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/FindYuni.cmake")

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(application)
ADD_SUBDIRECTORY(devices)
ADD_SUBDIRECTORY(script)
ADD_SUBDIRECTORY(threads)
#ADD_SUBDIRECTORY(ui)

