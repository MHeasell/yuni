CMake_minimum_required(VERSION 2.8)
include("../cmake/message.cmake")


YMESSAGE("")
YMESSAGE("Yuni Framework - Samples")
YMESSAGE("")
Project(YUNI-SAMPLES CXX)

IF(POLICY CMP0011)
	CMake_Policy(SET CMP0011 NEW)
ENDIF(POLICY CMP0011)


# To find 'FindYuni.cmake'
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../packages/cmake")

Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")

add_custom_target(samples)

Find_Package(Yuni COMPONENTS core)
IF(Yuni_FOUND)

	# Infos
	YMESSAGE("The Yuni Framework : ${Yuni_INFOS}")

	ADD_SUBDIRECTORY(audio)
	ADD_SUBDIRECTORY(core)
	ADD_SUBDIRECTORY(gfx)
	ADD_SUBDIRECTORY(devices)
	ADD_SUBDIRECTORY(jobs)
	ADD_SUBDIRECTORY(script)
	ADD_SUBDIRECTORY(threads)

ENDIF(Yuni_FOUND)

