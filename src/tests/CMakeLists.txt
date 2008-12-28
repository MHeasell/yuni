Project(YUNI-TESTS CXX)

Message(STATUS "")
Message(STATUS "Tests")
Message(STATUS "")


Include("${CMAKE_CURRENT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../Modules.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(automatic)
ADD_SUBDIRECTORY(manual)
