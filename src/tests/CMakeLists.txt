Project(YUNI-TESTS CXX)

CMake_minimum_required(VERSION 2.6)

IF(POLICY CMP0011)
	CMake_Policy(SET CMP0011 NEW)
ENDIF(POLICY CMP0011)


Message(STATUS "")
Message(STATUS "Tests")
Message(STATUS "")


Include("${CMAKE_CURRENT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(automatic)
ADD_SUBDIRECTORY(manual)
