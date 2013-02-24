
YMESSAGE_MODULE("DBI (Database independant)  (EXPERIMENTAL)")

LIBYUNI_CONFIG_LIB("both" "dbi"        "yuni-static-dbi")


# Sources for parsing JSON are imported from nany and no relative paths
# is currently provided
include_directories("..")

set (SRC_PRIVATE_DBI
	private/dbi/connector-data.h
	private/dbi/connector-data.cpp
	private/dbi/channel.h
	private/dbi/channel.hxx
	private/dbi/channel.cpp
)
source_group("DBI\\Private" FILES ${SRC_PRIVATE_DBI})

set(SRC_DBI
	dbi/dbi.h
	dbi/connector-pool.h
	dbi/connector-pool.hxx
	dbi/connector-pool.cpp
	dbi/error.h
	dbi/fwd.h
	dbi/transaction.h
	dbi/transaction.hxx
	dbi/transaction.cpp
	dbi/settings.h
	dbi/settings.hxx
)
source_group("DBI" FILES ${SRC_DBI})



add_Library(yuni-static-dbi STATIC
	${SRC_DBI}
	${SRC_PRIVATE_DBI}
)

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-dbi PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-dbi ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install net-related headers
install(
	DIRECTORY dbi
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)