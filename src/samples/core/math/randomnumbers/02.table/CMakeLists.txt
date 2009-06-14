
Message(STATUS "Sample: Core / Mathematics / Randomness / Random number table")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(math_rn_02_table main.cpp)
target_link_libraries(math_rn_02_table ${YUNI_STATIC_CORE})

