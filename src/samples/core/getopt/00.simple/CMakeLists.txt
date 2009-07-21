
Message(STATUS "Sample: Core / Command line Options (GetOpt) / Simple option")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(getopt_00_simple main.cpp)
target_link_libraries(getopt_00_simple ${YUNI_STATIC_CORE})

