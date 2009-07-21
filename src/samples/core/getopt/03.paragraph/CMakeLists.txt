
Message(STATUS "Sample: Core / Command line Options (GetOpt) / With text paragraph")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(getopt_03_paragraph main.cpp)
target_link_libraries(getopt_03_paragraph ${YUNI_STATIC_CORE})

