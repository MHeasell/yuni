YMESSAGE_MODULE("UUID")

LIBYUNI_CONFIG_LIB("both" "uuid" "yuni-static-uuid")
LIBYUNI_CONFIG_DEPENDENCY("uuid" "core") # core is required



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

# Install Algo-related headers
INSTALL(
	DIRECTORY algorithm
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)


