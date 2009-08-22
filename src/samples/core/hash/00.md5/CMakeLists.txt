
Message(STATUS "Sample: Core / Hash / Compute a MD5 checksum from a string")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(hash_00_md5 main.cpp)
target_link_libraries(hash_00_md5 ${YUNI_STATIC_CORE})
add_dependencies(samples hash_00_md5)

