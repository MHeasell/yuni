
Message(STATUS "Sample: Colors / RGBA")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(color_01_rgba main.cpp)
target_link_libraries(color_01_rgba ${YUNI_STATIC_CORE} ${YUNI_STATIC_GFX_CORE})

