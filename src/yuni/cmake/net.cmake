
YMESSAGE_MODULE("Network  (EXPERIMENTAL)")

LIBYUNI_CONFIG_LIB("both" "net"        "yuni-static-net")


set(SRC_NET_COMMON
	net/net.h
	net/errors.h
	net/errors.cpp
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

	net/messaging/worker.inc.hpp
	net/messaging/protocol.h
	net/messaging/protocol.hxx
	net/messaging/protocol.cpp
	net/messaging/schema.h
	net/messaging/schema.hxx
	net/messaging/message.h
	net/messaging/threadcontext.h
	net/messaging/threadcontext.hxx
)
source_group("Net\\Messaging" FILES ${SRC_NET_MESSAGE})

set(SRC_NET_MESSAGE_TRANSPORT
	net/messaging/transport.h
	net/messaging/transport/transport.h
	net/messaging/transport/transport.hxx
)
source_group("Net\\Messaging\\Transport" FILES ${SRC_NET_MESSAGE_TRANSPORT})

set(SRC_NET_MESSAGE_TRANSPORT_REST
	net/messaging/transport/rest/server.h
	net/messaging/transport/rest/server.cpp
	net/messaging/transport/rest/request.inc.hpp
)
source_group("Net\\Messaging\\Transport\\REST" FILES ${SRC_NET_MESSAGE_TRANSPORT_REST})
if (YUNI_HAS_STDINT_H)
	set_source_files_properties(net/messaging/transport/rest/mongoose.c PROPERTIES COMPILE_FLAGS -DHAVE_STDINT)
endif()


set(SRC_NET_MESSAGE_API
	net/messaging/api/methods.cpp
	net/messaging/api/methods.h
	net/messaging/api/methods.hxx
	net/messaging/api/fwd.h
	net/messaging/api/method.h
	net/messaging/api/method.cpp
	net/messaging/api/method.hxx
)
source_group("Net\\Messaging\\API" FILES ${SRC_NET_MESSAGE_API})


set(SRC_PRIVATE_NET_MESSAGE_TRANSPORT_REST
	private/net/messaging/transport/rest/mongoose.c
	private/net/messaging/transport/rest/mongoose.h
)
source_group("Private\\Net\\Messaging\\Transport\\REST" FILES ${SRC_PRIVATE_NET_MESSAGE_TRANSPORT_REST})


add_Library(yuni-static-net STATIC
	${SRC_NET_COMMON}
	${SRC_NET_MESSAGE}
	${SRC_NET_MESSAGE_API}
	${SRC_NET_MESSAGE_TRANSPORT}
	${SRC_NET_MESSAGE_TRANSPORT_REST}
	${SRC_PRIVATE_NET_MESSAGE_TRANSPORT_REST}
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
