
YMESSAGE("")
YMESSAGE("yuni-docmake")
YMESSAGE("")

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")
include_directories(tinyxml)

# Add definitions to help finding yuni parameters once installed (prefix + versioned path)
add_definitions("-DYUNI_VERSIONED_INST_PATH=\"${YUNI_VERSIONED_INST_PATH}\"")
add_definitions("-DYUNI_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
add_definitions("-DYUNI_SOURCE_TREE=\"${YUNI_SOURCE_TREE}\"")



set(src
	sqlite/sqlite3.c
	sqlite/sqlite3.h
	sqlite/sqlite3ext.h
	make.h
	make.cpp
	job.h
	job.cpp
	logs.h
	logs.cpp
	find-all-source-files.cpp
	main.cpp

	tinyxml/tinystr.cpp
	tinyxml/tinystr.h
	tinyxml/tinyxml.cpp
	tinyxml/tinyxml.h
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
	)

# Build the in-tree version of yuni-config.
add_executable(yuni-docmake ${src})

target_link_libraries(yuni-docmake  yuni-static-core)

