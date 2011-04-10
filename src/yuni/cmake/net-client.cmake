
YMESSAGE(":: [Module] Network Client  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

LIBYUNI_CONFIG_LIB("both" "net-client"        "yuni-static-net-client")



Set(SRC_NET 
		net/client/client.h
		net/client/client.cpp
	)
source_group("Network\\Server" FILES ${SRC_NET})

Add_Library(yuni-static-net-client STATIC ${SRC_NET})

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-net-client PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
INSTALL(TARGETS yuni-static-net-client ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install net-related headers
INSTALL(
	DIRECTORY net/client
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)
