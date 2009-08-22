
Message(STATUS "Sample: Core / Colors / Conversion between several RGB color models")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(color_00_rgb main.cpp)
target_link_libraries(color_00_rgb ${YUNI_STATIC_CORE})
add_dependencies(samples color_00_rgb)
