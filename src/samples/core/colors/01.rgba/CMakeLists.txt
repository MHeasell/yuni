
Message(STATUS "Sample: Core / Colors / Conversion between several RGBA color models")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(color_01_rgba main.cpp)
target_link_libraries(color_01_rgba ${YUNI_STATIC_CORE})
add_dependencies(samples color_01_rgba)

