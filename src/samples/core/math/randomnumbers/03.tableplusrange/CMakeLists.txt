
Message(STATUS "Sample: Core / Mathematics / Randomness / Random number table + Range")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(math_rn_03_table_plus_range main.cpp)
target_link_libraries(math_rn_03_table_plus_range ${YUNI_STATIC_CORE})
add_dependencies(samples math_rn_03_table_plus_range)

