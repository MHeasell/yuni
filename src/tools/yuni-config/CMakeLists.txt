IF(NOT YUNI_AUTO_COMPILE_YUNI_CONFIG)

	Project(yuni-config CXX)
	CMake_minimum_required(VERSION 2.8)

	IF(POLICY CMP0005)
		CMake_Policy(SET CMP0005 NEW)
	ENDIF(POLICY CMP0005)
	IF(POLICY CMP0011)
		CMake_Policy(SET CMP0011 NEW)
	ENDIF(POLICY CMP0011)

	Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/message.cmake")

ENDIF(NOT YUNI_AUTO_COMPILE_YUNI_CONFIG)
	
YMESSAGE("")
YMESSAGE("yuni-config")
YMESSAGE("")
IF(YUNI_AUTO_COMPILE_YUNI_CONFIG)
	YMESSAGE("(self)")
ENDIF(YUNI_AUTO_COMPILE_YUNI_CONFIG)


Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


Include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")

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

# Build the in-tree version of yuni-config.
ADD_EXECUTABLE(yuni-config ${src})
SET_TARGET_PROPERTIES(yuni-config PROPERTIES
	COMPILE_FLAGS "-DYUNI_YUNICONFIG_IN_TREE=\\\"${CMAKE_CURRENT_SOURCE_DIR}\\\""
	RUNTIME_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/bin"
) 

# If we are not bootstrapping, also build the "installable" yuni-config.
IF(NOT YUNI_BOOTSTRAP_YUNI_CONFIG)

	ADD_EXECUTABLE(yuni-config-${YUNI_VERSION} ${src})
	SET_TARGET_PROPERTIES(yuni-config-${YUNI_VERSION} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/bin") 
	INSTALL(TARGETS yuni-config-${YUNI_VERSION} RUNTIME DESTINATION bin)

ENDIF(NOT YUNI_BOOTSTRAP_YUNI_CONFIG)

