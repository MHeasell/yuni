
Message(STATUS "Sample: Core / Command line Options (GetOpt) / Remaining arguments")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(getopt_02_remainingargs main.cpp)
target_link_libraries(getopt_02_remainingargs ${YUNI_STATIC_CORE})

