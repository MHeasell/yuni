Project(YUNI-SAMPLES)

Message(STATUS "")
Message(STATUS "Samples for the Yuni Framework")
Message(STATUS "")
CMake_minimum_required(VERSION 2.6)


Include("${PROJECT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${PROJECT_SOURCE_DIR}/../FindYuni.cmake")


ADD_SUBDIRECTORY(sharedptr)
ADD_SUBDIRECTORY(colors)
ADD_SUBDIRECTORY(devices)
ADD_SUBDIRECTORY(application)
ADD_SUBDIRECTORY(hash)
ADD_SUBDIRECTORY(threads)


