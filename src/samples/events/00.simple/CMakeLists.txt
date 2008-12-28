
Message(STATUS "Sample: Events / Simple event management")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(events_00_simple main.cpp)
target_link_libraries(events_00_simple ${YUNI_STATIC_CORE})

