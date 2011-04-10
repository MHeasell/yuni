
YMESSAGE(":: [Module] Network Server  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

LIBYUNI_CONFIG_LIB("both" "net-server"        "yuni-static-net-server")



Set(SRC_NET 
		net/server/server.h
		net/server/server.cpp
	)
source_group("Network\\Server" FILES ${SRC_NET})

Add_Library(yuni-static-net-server STATIC ${SRC_NET})

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-net-server PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
INSTALL(TARGETS yuni-static-net-server ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install net-related headers
INSTALL(
	DIRECTORY net/server
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)
