
Message(STATUS "Sample: Core / Mathematics / Randomness / Typical use of a random number generator")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(math_rn_00_simple main.cpp)
target_link_libraries(math_rn_00_simple ${YUNI_STATIC_CORE})
add_dependencies(samples math_rn_00_simple)

