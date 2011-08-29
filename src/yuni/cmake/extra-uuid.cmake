YMESSAGE_MODULE("UUID")

LIBYUNI_CONFIG_LIB("both" "uuid" "yuni-static-uuid")
LIBYUNI_CONFIG_DEPENDENCY("uuid" "core") # core is required

if(NOT APPLE AND UNIX)
	# -luuid
	LIBYUNI_CONFIG_LIB("both", "uuid", "uuid")
endif()

if (WIN32 OR WIN64)
	# -lole32
	LIBYUNI_CONFIG_LIB("both", "uuid" "ole32")
	# -lrpcrt4
	LIBYUNI_CONFIG_LIB("both", "uuid" "rpcrt4")
endif()

if (UNIX)
	check_include_files("uuid/uuid.h" YUNI_HAS_UUID_H)
	if(NOT YUNI_HAS_UUID_H)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find uuid/uuid.h.")
		YMESSAGE(    " * Packages needed on Debian: libuuid1, uuid-dev")
		YMESSAGE(    " * Packages needed on redhat: libuuid-devel")
	endif()
endif()


add_library(yuni-static-uuid STATIC
	uuid/uuid.h
	uuid/uuid.hxx
	uuid/uuid.cpp
	uuid/fwd.h
	yuni.h
)

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-uuid PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
INSTALL(TARGETS yuni-static-uuid ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install UUID-related headers
INSTALL(
	DIRECTORY uuid
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)


