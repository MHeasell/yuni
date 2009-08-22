
Message(STATUS "Sample: Core / Command line Options (GetOpt) / Custom Help usage")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(getopt_04_customhelpusage main.cpp)
target_link_libraries(getopt_04_customhelpusage ${YUNI_STATIC_CORE})
add_dependencies(samples getopt_04_customhelpusage)

