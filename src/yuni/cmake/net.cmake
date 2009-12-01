
Message(STATUS ":: [Module] Network")

LIBYUNI_CONFIG_LIB("net"        "yuni-static-net")



Set(SRC_NET  net/protocol.h  net/protocol.cpp)
source_group("Network\\Protocol" FILES ${SRC_NET})

Add_Library(yuni-static-net STATIC ${SRC_NET})

