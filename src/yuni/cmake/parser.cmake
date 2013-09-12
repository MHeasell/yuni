
YMESSAGE_MODULE("Parser Generator")

LIBYUNI_CONFIG_LIB("both" "parser"        "yuni-static-parser")



include_directories("..")



set(SRC_PARSER
	parser/peg/grammar.h
	parser/peg/grammar.hxx
	parser/peg/grammar.cpp
	parser/peg/node.h
	parser/peg/node.hxx
	parser/peg/node.cpp
)
source_group("Parser\\Generator" FILES ${SRC_PARSER})



add_Library(yuni-static-parser STATIC
	${SRC_PARSER}
)

# Setting output path
SET_TARGET_PROPERTIES(yuni-static-parser PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-parser ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

# Install net-related headers
install(
	DIRECTORY parser
	DESTINATION include/${YUNI_VERSIONED_INST_PATH}/yuni
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)
