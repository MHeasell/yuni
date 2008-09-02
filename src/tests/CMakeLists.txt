Project(YUNI-TESTS)

Message(STATUS "")
Message(STATUS "Tests for the Yuni Framework")
Message(STATUS "")
CMake_minimum_required(VERSION 2.6)


Include("${PROJECT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${PROJECT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(automatic)
