
Message(STATUS "Sample: Multi-Threading / Using Condition Variable for Thread Synchronization")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(threads_01_condition main.cpp)
target_link_libraries(threads_01_condition ${YUNI_STATIC_CORE} ${YUNI_STATIC_ALGORITHMS})

