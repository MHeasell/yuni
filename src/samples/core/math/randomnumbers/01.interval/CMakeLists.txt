
Message(STATUS "Sample: Core / Mathematics / Randomness / Random numbers within a range")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(math_rn_01_range main.cpp)
target_link_libraries(math_rn_01_range ${YUNI_STATIC_CORE})

