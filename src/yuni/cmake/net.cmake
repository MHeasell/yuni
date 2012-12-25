
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
	net/message/service.h
	net/message/service.cpp
	net/message/service.hxx
	net/message/fwd.h

	net/message/transport.h
	net/message/transport/transport.h
	net/message/transport/transport.hxx
	net/message/worker.h
	net/message/worker.hxx
	net/message/worker.cpp
	net/message/protocol.h

	net/message/transport/rest/mongoose.c
	net/message/transport/rest/mongoose.h
)
source_group("Net\\Message" FILES ${SRC_NET_MESSAGE})

set(SRC_NET_MESSAGE_TRANSPORT_REST
	net/message/transport/rest/mongoose.c
	net/message/transport/rest/mongoose.h
)
source_group("Net\\Message\\Transport" FILES ${SRC_NET_MESSAGE_TRANSPORT_REST})


set(SRC_NET_MESSAGE_API
	net/message/api/methods.cpp
	net/message/api/methods.h
	net/message/api/methods.hxx
	net/message/api/fwd.h
	net/message/api/method.h
	net/message/api/method.hxx
)
source_group("Net\\Message\\API" FILES ${SRC_NET_MESSAGE_API})



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
