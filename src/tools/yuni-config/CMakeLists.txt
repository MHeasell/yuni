
IF(NOT YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)

	Project(Libyuni-Config CXX)
	CMake_minimum_required(VERSION 2.8)

	IF(POLICY CMP0005)
		CMake_Policy(SET CMP0005 NEW)
	ENDIF(POLICY CMP0005)
	IF(POLICY CMP0011)
		CMake_Policy(SET CMP0011 NEW)
	ENDIF(POLICY CMP0011)

	Set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../build/${YUNI_TARGET}/bin")

	Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/message.cmake")
ENDIF(NOT YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)

YMESSAGE("")
YMESSAGE("yuni-config")
YMESSAGE("")
IF(YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)
	YMESSAGE("(self)")
ENDIF(YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)


Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")

# Disable all code related to thread-safety
ADD_DEFINITIONS("-DYUNI_NO_THREAD_SAFE")

# Add definitions to help finding yuni parameters once installed (prefix + versioned path)
ADD_DEFINITIONS("-DYUNI_VERSIONED_INST_PATH=\"${YUNI_VERSIONED_INST_PATH}\"")
ADD_DEFINITIONS("-DYUNI_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DYUNI_SOURCE_TREE=\"${YUNI_SOURCE_TREE}\"")



SET(src
	../../yuni/core/version/version.cpp
	../../yuni/core/getopt/option.cpp ../../yuni/core/getopt/parser.cpp
	../../yuni/core/io/io.cpp
	../../yuni/core/io/file/file.cpp
	../../yuni/core/io/file/load.cpp
	../../yuni/core/io/file/openmode.cpp
	../../yuni/core/io/file/stream.cpp
	../../yuni/core/io/exists.cpp
	../../yuni/core/io/directory/current.cpp

	# iterator
	../../yuni/core/io/directory/iterator.h
	../../yuni/core/io/directory/iterator/iterator.h
	../../yuni/core/io/directory/iterator/iterator.hxx
	../../yuni/core/io/directory/iterator/iterator.cpp
	../../yuni/core/io/directory/iterator/detachedthread.h

	versions.h versions.hxx versions.cpp
	program.h program.hxx program.cpp
	main.cpp)


ADD_EXECUTABLE(yuni-config                  ${src})
ADD_EXECUTABLE(yuni-config-${YUNI_VERSION}  ${src})

SET_TARGET_PROPERTIES(yuni-config PROPERTIES COMPILE_FLAGS "-DYUNI_YUNICONFIG_IN_TREE=\\\"${CMAKE_CURRENT_SOURCE_DIR}\\\"")

# Setting install path 
SET_TARGET_PROPERTIES(yuni-config PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/bin") 
SET_TARGET_PROPERTIES(yuni-config-${YUNI_VERSION} PROPERTIES  RUNTIME_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/bin") 

# Install
INSTALL(TARGETS yuni-config-${YUNI_VERSION} RUNTIME DESTINATION bin)


# Stripping 
IF(YUNI_TARGET_RELEASE) 
	IF(UNIX) 
		YMESSAGE("Stripping 'yuni-config': yes") 
		ADD_CUSTOM_COMMAND(TARGET yuni-config POST_BUILD COMMAND ${CMAKE_STRIP} "${YUNI_OUTPUT_DIRECTORY}/bin/yuni-config") 
		ADD_CUSTOM_COMMAND(TARGET yuni-config-${YUNI_VERSION} POST_BUILD COMMAND ${CMAKE_STRIP} "${YUNI_OUTPUT_DIRECTORY}/bin/yuni-config-${YUNI_VERSION}") 
	ENDIF()
ENDIF()

