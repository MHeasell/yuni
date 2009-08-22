Project(Libyuni-Config CXX)

CMake_minimum_required(VERSION 2.6)

IF(POLICY CMP0011)
	CMake_Policy(SET CMP0011 NEW)
ENDIF(POLICY CMP0011)


Message(STATUS "")
Message(STATUS "libyuni-config")
Message(STATUS "")


Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/FindYuni.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")
ADD_EXECUTABLE(libyuni-config main.cpp versions.cpp)
target_link_libraries(libyuni-config yuni-static-core)
