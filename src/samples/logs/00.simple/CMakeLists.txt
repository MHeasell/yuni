
Message(STATUS "Sample: Logs / Hello World")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(logs_00_simple main.cpp)
target_link_libraries(logs_00_simple ${YUNI_STATIC_CORE})

