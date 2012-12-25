
YMESSAGE_MODULE("Network  (EXPERIMENTAL)")

LIBYUNI_CONFIG_LIB("both" "net"        "yuni-static-net")


set(SRC_NET_COMMON
	net/net.h
	net/errors.h
	net/port.h
	net/port.hxx
	net/hostaddressport.h
	net/hostaddressport.hxx
	net/protocol.h
	net/protocol.cpp
)
source_group("Net" FILES ${SRC_NET_COMMUN})


set(SRC_NET_MESSAGE
	net/messaging/service.h
	net/messaging/service.cpp
	net/messaging/service.hxx
	net/messaging/fwd.h

	net/messaging/transport.h
	net/messaging/transport/transport.h
	net/messaging/transport/transport.hxx
	net/messaging/worker.h
	net/messaging/worker.hxx
	net/messaging/worker.cpp
	net/messaging/protocol.h

	net/messaging/transport/rest/mongoose.c
	net/messaging/transport/rest/mongoose.h
)
source_group("Net\\Messaging" FILES ${SRC_NET_MESSAGE})

set(SRC_NET_MESSAGE_TRANSPORT_REST
	net/messaging/transport/rest/mongoose.c
	net/messaging/transport/rest/mongoose.h
)
source_group("Net\\Messaging\\Transport" FILES ${SRC_NET_MESSAGE_TRANSPORT_REST})


set(SRC_NET_MESSAGE_API
	net/messaging/api/methods.cpp
	net/messaging/api/methods.h
	net/messaging/api/methods.hxx
	net/messaging/api/fwd.h
	net/messaging/api/method.h
	net/messaging/api/method.hxx
)
source_group("Net\\Messaging\\API" FILES ${SRC_NET_MESSAGE_API})



add_Library(yuni-static-net STATIC
	${SRC_NET_COMMON}
	${SRC_NET_MESSAGE}
	${SRC_NET_MESSAGE_API}
	${SRC_NET_MESSAGE_TRANSPORT_REST}
	${SRC_NET_MSG})

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-net PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-net ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install net-related headers
install(
	DIRECTORY net
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)
