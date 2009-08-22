
Message(STATUS "Sample: Core / Command line Options (GetOpt) / With various types")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(getopt_01_varioustypes main.cpp)
target_link_libraries(getopt_01_varioustypes ${YUNI_STATIC_CORE})
add_dependencies(samples getopt_01_varioustypes)

