
Message(STATUS "Sample: Core / Hash / Compute a MD5 checksum from a file")
include_directories(${YUNI_INCLUDE})
ADD_EXECUTABLE(hash_01_md5_fromfile main.cpp)
target_link_libraries(hash_01_md5_fromfile ${YUNI_STATIC_CORE})
add_dependencies(samples hash_01_md5_fromfile)

