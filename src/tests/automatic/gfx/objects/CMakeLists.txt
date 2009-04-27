
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(test-gfx-objects main.cpp)
target_link_libraries(test-gfx-objects ${YUNI_STATIC_CORE})

