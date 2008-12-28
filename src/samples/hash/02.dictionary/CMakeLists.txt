
Message(STATUS "Sample: Hash / Simple dictionary management")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(hash_02_dictionary main.cpp)
target_link_libraries(hash_02_dictionary ${YUNI_STATIC_CORE})

