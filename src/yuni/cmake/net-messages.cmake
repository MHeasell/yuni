
YMESSAGE_MODULE("Network Messages  (EXPERIMENTAL)")

LIBYUNI_CONFIG_LIB("both" "net-messages"        "yuni-static-net-messages")



Set(SRC_NET
	net/messaging/protocol.h
	net/messaging/service.cpp
	net/messaging/service.h
	net/messaging/service.hxx
	net/messaging/worker.h
	net/messaging/worker.hxx
	net/messaging/worker.cpp
	net/messaging/api/method.h
	net/messaging/api/method.hxx
	net/messaging/api/methods.cpp
	net/messaging/api/methods.h
	net/messaging/api/methods.hxx
	net/messaging/transport.h
	net/messaging/transport
	net/messaging/transport/transport.h
	net/messaging/transport/transport.hxx
	net/messaging/transport/rest/mongoose.h
	net/messaging/transport/rest/mongoose.c
	)
source_group("Network\\Messages" FILES ${SRC_NET})

Add_Library(yuni-static-net-messages STATIC ${SRC_NET})

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-net-messages PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
INSTALL(TARGETS yuni-static-net-messages ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

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
