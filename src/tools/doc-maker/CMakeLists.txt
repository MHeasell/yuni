
YMESSAGE("")
YMESSAGE("doc-maker")
YMESSAGE("")

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CommonSettings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules.cmake")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../..")

# Disable all code related to thread-safety
add_definitions("-DYUNI_NO_THREAD_SAFE")

# Add definitions to help finding yuni parameters once installed (prefix + versioned path)
add_definitions("-DYUNI_VERSIONED_INST_PATH=\"${YUNI_VERSIONED_INST_PATH}\"")
add_definitions("-DYUNI_INSTALL_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
add_definitions("-DYUNI_SOURCE_TREE=\"${YUNI_SOURCE_TREE}\"")



set(src
	main.cpp)

# Build the in-tree version of yuni-config.
add_executable(docmaker ${src})

target_link_libraries(docmaker  yuni-static-core)

