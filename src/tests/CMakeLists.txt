Project(YUNI-TESTS CXX)

Message(STATUS "")
Message(STATUS "Tests")
Message(STATUS "")
CMake_minimum_required(VERSION 2.6)


Include("${PROJECT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${PROJECT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(automatic)
