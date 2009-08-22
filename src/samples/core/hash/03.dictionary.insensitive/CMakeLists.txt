
Message(STATUS "Sample: Core / Hash / Dictionary with insensitive keys")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(hash_03_dictionary_insensitive main.cpp)
target_link_libraries(hash_03_dictionary_insensitive ${YUNI_STATIC_CORE})
add_dependencies(samples hash_03_dictionary_insensitive)

