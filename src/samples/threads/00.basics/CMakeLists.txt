
Message(STATUS "Sample: Multi-Threading / A Simple custom thread")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(threads_00_basics main.cpp)
target_link_libraries(threads_00_basics ${YUNI_STATIC_CORE})
add_dependencies(samples threads_00_basics)

